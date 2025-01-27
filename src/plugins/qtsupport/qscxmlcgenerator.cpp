/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of Qt Creator.
**
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
****************************************************************************/

#include "qscxmlcgenerator.h"

#include <qtsupport/baseqtversion.h>
#include <qtsupport/qtkitinformation.h>
#include <projectexplorer/target.h>
#include <utils/qtcassert.h>

#include <QDateTime>
#include <QLoggingCategory>
#include <QUuid>

using namespace ProjectExplorer;

namespace QtSupport {

static QLoggingCategory log("qtc.qscxmlcgenerator", QtWarningMsg);
static const char TaskCategory[] = "Task.Category.ExtraCompiler.QScxmlc";

QScxmlcGenerator::QScxmlcGenerator(const Project *project,
                                   const Utils::FilePath &source,
                                   const Utils::FilePaths &targets, QObject *parent) :
    ProcessExtraCompiler(project, source, targets, parent),
    m_tmpdir("qscxmlgenerator")
{
    QTC_ASSERT(targets.count() == 2, return);
    m_header = m_tmpdir.filePath(targets[0].fileName()).toString();
    m_impl = m_tmpdir.filePath(targets[1].fileName()).toString();
}

Tasks QScxmlcGenerator::parseIssues(const QByteArray &processStderr)
{
    Tasks issues;
    foreach (const QByteArray &line, processStderr.split('\n')) {
        QByteArrayList tokens = line.split(':');

        if (tokens.length() > 4) {
            Utils::FilePath file = Utils::FilePath::fromUtf8(tokens[0]);
            int line = tokens[1].toInt();
            // int column = tokens[2].toInt(); <- nice, but not needed for now.
            Task::TaskType type = tokens[3].trimmed() == "error" ?
                        Task::Error : Task::Warning;
            QString message = QString::fromUtf8(tokens.mid(4).join(':').trimmed());
            issues.append(Task(type, message, file, line, TaskCategory));
        }
    }
    return issues;
}


Utils::FilePath QScxmlcGenerator::command() const
{
    QtSupport::BaseQtVersion *version = nullptr;
    Target *target;
    if ((target = project()->activeTarget()))
        version = QtSupport::QtKitAspect::qtVersion(target->kit());
    else
        version = QtSupport::QtKitAspect::qtVersion(KitManager::defaultKit());

    if (!version)
        return Utils::FilePath();

    return version->qscxmlcFilePath();
}

QStringList QScxmlcGenerator::arguments() const
{
    QTC_ASSERT(!m_header.isEmpty(), return QStringList());

    return QStringList({QLatin1String("--header"), m_header, QLatin1String("--impl"), m_impl,
                        tmpFile().fileName()});
}

Utils::FilePath QScxmlcGenerator::workingDirectory() const
{
    return m_tmpdir.path();
}

bool QScxmlcGenerator::prepareToRun(const QByteArray &sourceContents)
{
    const Utils::FilePath fn = tmpFile();
    QFile input(fn.toString());
    if (!input.open(QIODevice::WriteOnly))
        return false;
    input.write(sourceContents);
    input.close();

    return true;
}

FileNameToContentsHash QScxmlcGenerator::handleProcessFinished(Utils::QtcProcess *process)
{
    Q_UNUSED(process)
    const Utils::FilePath wd = workingDirectory();
    FileNameToContentsHash result;
    forEachTarget([&](const Utils::FilePath &target) {
        const Utils::FilePath file = wd.pathAppended(target.fileName());
        QFile generated(file.toString());
        if (!generated.open(QIODevice::ReadOnly))
            return;
        result[target] = generated.readAll();
    });
    return result;
}

Utils::FilePath QScxmlcGenerator::tmpFile() const
{
    return workingDirectory().pathAppended(source().fileName());
}

FileType QScxmlcGeneratorFactory::sourceType() const
{
    return FileType::StateChart;
}

QString QScxmlcGeneratorFactory::sourceTag() const
{
    return QStringLiteral("scxml");
}

ExtraCompiler *QScxmlcGeneratorFactory::create(
        const Project *project, const Utils::FilePath &source,
        const Utils::FilePaths &targets)
{
    return new QScxmlcGenerator(project, source, targets, this);
}

} // namespace QtSupport
