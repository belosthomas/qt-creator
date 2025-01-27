/****************************************************************************
**
** Copyright (C) 2016 BlackBerry Limited. All rights reserved.
** Contact: BlackBerry (qt@blackberry.com), KDAB (info@kdab.com)
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

#include <projectexplorer/gcctoolchain.h>
#include <projectexplorer/gcctoolchainfactories.h>

namespace Qnx {
namespace Internal {

class QnxToolChain : public ProjectExplorer::GccToolChain
{
    Q_DECLARE_TR_FUNCTIONS(Qnx::Internal::QnxToolChain)

public:
    QnxToolChain();

    std::unique_ptr<ProjectExplorer::ToolChainConfigWidget> createConfigurationWidget() override;

    void addToEnvironment(Utils::Environment &env) const override;
    QStringList suggestedMkspecList() const override;

    QVariantMap toMap() const override;
    bool fromMap(const QVariantMap &data) override;

    Utils::FilePath sdpPath() const;
    void setSdpPath(const Utils::FilePath &sdpPath);
    QString cpuDir() const;
    void setCpuDir(const QString &cpuDir);

    bool operator ==(const ToolChain &) const override;

protected:
    DetectedAbisResult detectSupportedAbis() const override;

private:
    Utils::FilePath m_sdpPath;
    QString m_cpuDir;
};

// --------------------------------------------------------------------------
// QnxToolChainFactory
// --------------------------------------------------------------------------

class QnxToolChainFactory : public ProjectExplorer::ToolChainFactory
{
public:
    QnxToolChainFactory();

    QList<ProjectExplorer::ToolChain *> autoDetect(
            const QList<ProjectExplorer::ToolChain *> &alreadyKnown,
            const ProjectExplorer::IDevice::Ptr &device) final;
};

//----------------------------------------------------------------------------
// QnxToolChainConfigWidget
//----------------------------------------------------------------------------

class QnxToolChainConfigWidget : public ProjectExplorer::ToolChainConfigWidget
{
    Q_OBJECT

public:
    QnxToolChainConfigWidget(QnxToolChain *tc);

private:
    void applyImpl() override;
    void discardImpl() override;
    bool isDirtyImpl() const override;
    void makeReadOnlyImpl() override { }

    void handleSdpPathChange();

    Utils::PathChooser *m_compilerCommand;
    Utils::PathChooser *m_sdpPath;
    ProjectExplorer::AbiWidget *m_abiWidget;

};

} // namespace Internal
} // namespace Qnx
