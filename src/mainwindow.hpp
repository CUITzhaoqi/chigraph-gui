#pragma once

#ifndef CHIGGUI_MAINWINDOW_H
#define CHIGGUI_MAINWINDOW_H

#include <KStandardAction>
#include <KXmlGuiWindow>
#include <QListView>
#include <QPlainTextEdit>
#include <QProcess>
#include <QTabWidget>
#include <QUrl>
#include <chi/Context.hpp>
#include <chi/Fwd.hpp>
#include <nodes/FlowScene>
#include <nodes/FlowView>

#include "functionview.hpp"
#include "launchconfigurationmanager.hpp"

class ModuleBrowser;
class ThemeManager;
class CentralTabView;

class MainWindow : public KXmlGuiWindow {
	Q_OBJECT
public:
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow();

	chi::Context&   context() const { return *mChigContext; }
	CentralTabView& tabView() const { return *mFunctionTabs; }

	LaunchConfigurationManager& launchManager() { return *mLaunchManager; }

	/// Load a module into the window.
	/// \exepcts `!name.isEmpty()`
	std::pair<chi::Result, chi::GraphModule*> loadModule(const QString& name);

private:
	static MainWindow* mInstance;

public:
	static MainWindow* instance() { return mInstance; }

public slots:
	void openWorkspaceDialog();           // this one opens a dialog
	void openWorkspace(const QUrl& url);  // and this one doesn't
	void newWorkspace();
	void save();

	void moduleDirtied(chi::GraphModule& mod);

signals:
	void workspaceOpened(chi::Context& workspace);
	void functionOpened(FunctionView* func);

	void newModuleCreated(chi::GraphModule& newModule);
	void newFunctionCreated(chi::GraphFunction& func);

private:
	void closeEvent(QCloseEvent* event) override;

	void updateUsableConfigs();

	std::unique_ptr<LaunchConfigurationManager> mLaunchManager;

	KRecentFilesAction* mOpenRecentAction;  // keep this so we can save the entries

	KSelectAction* mConfigSelectAction;

	// the tabs for open functions
	CentralTabView* mFunctionTabs = nullptr;

	// context & module
	std::unique_ptr<chi::Context> mChigContext   = nullptr;
	ModuleBrowser*                mModuleBrowser = nullptr;

	std::unique_ptr<ThemeManager> mThemeManager;
};

#endif  // CHIGGUI_MAINWINDOW_H
