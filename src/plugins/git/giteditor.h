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

#pragma once

#include <vcsbase/vcsbaseeditor.h>

#include <QRegularExpression>

namespace Utils {
class FancyLineEdit;
class FilePath;
} // Utils

namespace Git {
namespace Internal {

class GitLogFilterWidget;

class GitEditorWidget : public VcsBase::VcsBaseEditorWidget
{
    Q_OBJECT

public:
    GitEditorWidget();

    void setPlainText(const QString &text) override;
    QWidget *addFilterWidget();
    void setPickaxeLineEdit(Utils::FancyLineEdit *lineEdit);
    QString grepValue() const;
    QString pickaxeValue() const;
    bool caseSensitive() const;
    void refresh();

signals:
    void toggleFilters(bool value);

private:
    void applyDiffChunk(const VcsBase::DiffChunk& chunk, bool revert);

    void init() override;
    void addDiffActions(QMenu *menu, const VcsBase::DiffChunk &chunk) override;
    void aboutToOpen(const Utils::FilePath &filePath, const Utils::FilePath &realFilePath) override;
    QString changeUnderCursor(const QTextCursor &) const override;
    VcsBase::BaseAnnotationHighlighter *createAnnotationHighlighter(const QSet<QString> &changes) const override;
    QString decorateVersion(const QString &revision) const override;
    QStringList annotationPreviousVersions(const QString &revision) const override;
    bool isValidRevision(const QString &revision) const override;
    void addChangeActions(QMenu *menu, const QString &change) override;
    QString revisionSubject(const QTextBlock &inBlock) const override;
    bool supportChangeLinks() const override;
    QString fileNameForLine(int line) const override;
    Utils::FilePath sourceWorkingDirectory() const;

    const QRegularExpression m_changeNumberPattern;
    GitLogFilterWidget *m_logFilterWidget = nullptr;
};

} // namespace Git
} // namespace Internal
