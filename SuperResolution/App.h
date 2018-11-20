#pragma once

#include "pch.h"
#include "Common\DeviceResources.h"
#include "SuperResolutionMain.h"

namespace SuperResolution
{
	// Main entry point for our app. Connects the app with the Windows shell and handles application lifecycle events.
	class App sealed : public Windows::ApplicationModel::Core::IFrameworkView
	{
	public:
		App();

		// IFrameworkView methods.
		virtual void Initialize(Windows::ApplicationModel::Core::CoreApplicationView const& applicationView);
		virtual void SetWindow(Windows::UI::Core::CoreWindow const& window);
		virtual void Load(winrt::hstring const& entryPoint);
		virtual void Run();
		virtual void Uninitialize();

	protected:
		// Application lifecycle event handlers.
		void OnActivated(Windows::ApplicationModel::Core::CoreApplicationView const& applicationView, Windows::ApplicationModel::Activation::IActivatedEventArgs const& args);
		void OnSuspending(IInspectable const& sender, Windows::ApplicationModel::SuspendingEventArgs const& args);
		void OnResuming(IInspectable const& sender, IInspectable const& args);

		// Window event handlers.
		void OnWindowSizeChanged(Windows::UI::Core::CoreWindow const& sender, Windows::UI::Core::WindowSizeChangedEventArgs const&  args);
		void OnVisibilityChanged(Windows::UI::Core::CoreWindow const&  sender, Windows::UI::Core::VisibilityChangedEventArgs const&  args);
		void OnWindowClosed(Windows::UI::Core::CoreWindow const&  sender, Windows::UI::Core::CoreWindowEventArgs const&  args);

		// DisplayInformation event handlers.
		void OnDpiChanged(Windows::Graphics::Display::DisplayInformation const&  sender, IInspectable const& args);
		void OnOrientationChanged(Windows::Graphics::Display::DisplayInformation const&  sender, IInspectable const& args);
		void OnDisplayContentsInvalidated(Windows::Graphics::Display::DisplayInformation const& sender, IInspectable const& args);

	private:
		// Private accessor for m_deviceResources, protects against device removed errors.
		std::shared_ptr<DX::DeviceResources> GetDeviceResources();
		
		std::shared_ptr<DX::DeviceResources> m_deviceResources;
		std::unique_ptr<SuperResolutionMain> m_main;
		bool m_windowClosed;
		bool m_windowVisible;
	};
}

class Direct3DApplicationSource sealed : Windows::ApplicationModel::Core::IFrameworkViewSource
{
public:
	virtual Windows::ApplicationModel::Core::IFrameworkView CreateView();
};
