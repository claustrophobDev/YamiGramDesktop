// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2026

#include "ayu/features/streamer_mode/platform/streamer_mode_win.h"

#include "core/application.h"
#include "window/window_controller.h"

namespace AyuFeatures::StreamerMode::Impl {

namespace {

void applyToWindow(HWND hwnd, bool hide) {
	if (!hwnd) {
		return;
	}
	const auto root = GetAncestor(hwnd, GA_ROOT);
	SetWindowDisplayAffinity(
		root ? root : hwnd,
		hide ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE);
}

BOOL CALLBACK enumProc(HWND hwnd, LPARAM param) {
	auto processId = DWORD(0);
	GetWindowThreadProcessId(hwnd, &processId);
	if (processId == GetCurrentProcessId()) {
		SetWindowDisplayAffinity(
			hwnd,
			param ? WDA_EXCLUDEFROMCAPTURE : WDA_NONE);
	}
	return TRUE;
}

void applyToProcess(bool hide) {
	EnumWindows(enumProc, hide ? 1 : 0);
}

} // namespace

void enableHook() {
	applyToProcess(true);
	Core::App().enumerateWindows([&](not_null<Window::Controller*> w) {
		applyToWindow(reinterpret_cast<HWND>(w->widget()->winId()), true);
	});
}

void disableHook() {
	applyToProcess(false);
	Core::App().enumerateWindows([&](not_null<Window::Controller*> w) {
		applyToWindow(reinterpret_cast<HWND>(w->widget()->winId()), false);
	});
}

void hideWidgetWindow(QWidget *widget) {
	applyToWindow(reinterpret_cast<HWND>(widget->window()->winId()), true);
}

void showWidgetWindow(QWidget *widget) {
	applyToWindow(reinterpret_cast<HWND>(widget->window()->winId()), false);
}

}
