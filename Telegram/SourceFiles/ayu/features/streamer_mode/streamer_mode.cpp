// This is the source code of AyuGram for Desktop.
//
// We do not and cannot prevent the use of our code,
// but be respectful and credit the original author.
//
// Copyright @Radolyn, 2026

#include "ayu/features/streamer_mode/streamer_mode.h"

#include "ayu/ayu_settings.h"
#include "window/window_controller.h"

#if defined Q_OS_WINRT || defined Q_OS_WIN
#include "ayu/features/streamer_mode/platform/streamer_mode_win.h"
#elif defined Q_OS_MAC // Q_OS_WINRT || Q_OS_WIN
#include "ayu/features/streamer_mode/platform/streamer_mode_mac.h"
#else // Q_OS_WINRT || Q_OS_WIN || Q_OS_MAC
#include "ayu/features/streamer_mode/platform/streamer_mode_linux.h"
#endif // else for Q_OS_WINRT || Q_OS_WIN || Q_OS_MAC

namespace AyuFeatures::StreamerMode
{

bool isEnabledVal;

bool isEnabled()
{
	return isEnabledVal;
}

void apply(bool enabled)
{
	isEnabledVal = enabled;
	if (enabled) {
		Impl::enableHook();
	} else {
		Impl::disableHook();
	}
}

void enable()
{
	AyuSettings::getInstance().setStreamerMode(true);
}

void disable()
{
	AyuSettings::getInstance().setStreamerMode(false);
}

void restore()
{
	apply(AyuSettings::getInstance().streamerMode());
}

void hideWidgetWindow(QWidget *widget)
{
	Impl::hideWidgetWindow(widget);
}

void showWidgetWindow(QWidget *widget)
{
	Impl::showWidgetWindow(widget);
}

}
