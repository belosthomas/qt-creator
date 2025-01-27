############################################################################
#
# Copyright (C) 2016 The Qt Company Ltd.
# Contact: https://www.qt.io/licensing/
#
# This file is part of Qt Creator.
#
# Commercial License Usage
# Licensees holding valid commercial Qt licenses may use this file in
# accordance with the commercial license agreement provided with the
# Software or, alternatively, in accordance with the terms contained in
# a written agreement between you and The Qt Company. For licensing terms
# and conditions see https://www.qt.io/terms-conditions. For further
# information use the contact form at https://www.qt.io/contact-us.
#
# GNU General Public License Usage
# Alternatively, this file may be used under the terms of the GNU
# General Public License version 3 as published by the Free Software
# Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
# included in the packaging of this file. Please review the following
# information to ensure the GNU General Public License requirements will
# be met: https://www.gnu.org/licenses/gpl-3.0.html.
#
############################################################################

source("../../shared/qtcreator.py")

def main():
    startQC()
    if not startedWithoutPluginError():
        return
    # using a temporary directory won't mess up a potentially existing
    workingDir = tempDir()
    projectName = createNewQtQuickApplication(workingDir)[1]
    editor = waitForObject(":Qt Creator_QmlJSEditor::QmlJSTextEditorWidget")
    if placeCursorToLine(editor, "}"):
        type(editor, '<Left>')
        type(editor, '<Return>')
        type(editor, '<Up>')
        type(editor, '<Return>')
        typeLines(editor, ['Timer {',
                           'interval: 1000',
                           'running: true',
                           'onTriggered: console.log("Break here")'])
        invokeMenuItem("File", "Save All")
        filesAndLines = [
                        { "%s.Sources.main\\.cpp" % projectName : "QQmlApplicationEngine engine;" },
                        { "%s.Resources.qml\.qrc./.main\\.qml" % projectName : 'onTriggered.*' }
                        ]
        test.log("Setting breakpoints")
        expectedBreakpointsOrder = setBreakpointsForCurrentProject(filesAndLines)
        if expectedBreakpointsOrder:
            availableConfigs = iterateBuildConfigs("Debug")
            if len(availableConfigs) > 1:  # having just one config means no change, no progress bar
                progressBarWait()
            elif len(availableConfigs) == 0:
                test.fatal("Haven't found a suitable Qt version - leaving without debugging.")
            for kit, config in availableConfigs:
                test.log("Selecting '%s' as build config" % config)
                verifyBuildConfig(kit, config, True, True, True)
                # explicitly build before start debugging for adding the executable as allowed program to WinFW
                selectFromLocator("t rebuild", "Rebuild (Rebuild All Projects)")
                waitForCompile(300000)
                if not checkCompile():
                    test.fatal("Compile had errors... Skipping current build config")
                    continue
                if platform.system() in ('Microsoft' 'Windows'):
                    switchViewTo(ViewConstants.PROJECTS)
                    switchToBuildOrRunSettingsFor(kit, ProjectSettings.BUILD)
                    buildDir = os.path.join(str(waitForObject(":Qt Creator_Utils::BuildDirectoryLineEdit").text),
                                            "debug")
                    switchViewTo(ViewConstants.EDIT)
                    allowAppThroughWinFW(buildDir, projectName, None)
                if not doSimpleDebugging(kit, config, expectedBreakpointsOrder):
                    try:
                        stopB = findObject(':Qt Creator.Stop_QToolButton')
                        if stopB.enabled:
                            clickButton(stopB)
                    except:
                        pass
                if platform.system() in ('Microsoft' 'Windows'):
                    deleteAppFromWinFW(buildDir, projectName, None)
                # close application output window of current run to avoid mixing older output on the next run
                ensureChecked(":Qt Creator_AppOutput_Core::Internal::OutputPaneToggleButton")
                clickButton(waitForObject("{type='CloseButton' unnamed='1' visible='1' "
                                          "window=':Qt Creator_Core::Internal::MainWindow'}"))
                try:
                    clickButton(waitForObject(":Close Debugging Session.Yes_QPushButton", 2000))
                except:
                    pass
        else:
            test.fatal("Setting breakpoints failed - leaving without testing.")
    invokeMenuItem("File", "Exit")
