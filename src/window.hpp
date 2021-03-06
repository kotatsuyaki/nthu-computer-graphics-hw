#ifndef WINDOW_HPP_
#define WINDOW_HPP_

#include <functional>
#include <memory>
#include <string>

// Wrapper class for GLFW initialization / termination.
//
// Existence of an instance of this guarantees that the GLFW library has been initialized.
// Upon destruction, GLFW is terminated automatically.
class Glfw final {
  public:
    Glfw();
    ~Glfw();

    // Prevent copy
    Glfw(const Glfw&) = delete;
    Glfw& operator=(const Glfw&) = delete;

    // Allow move
    Glfw(Glfw&&) = default;
    Glfw& operator=(Glfw&&) = default;
};

// Key and action types to avoid leaking underlying impl
enum class Key { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };
enum class KeyAction { Down, Up };

// Callback types used in windows.
using KeyCallback = std::function<void()>;
using ScrollCallback = std::function<void(float, float)>;
using MouseButtonCallback = std::function<void(KeyAction)>;
using CursorPosCallback = std::function<void(float, float)>;
using FbSizeCallback = std::function<void(int, int)>;

// Wrapper class for GLFW windows.
class Window final {
  public:
    // Constructs a window and makes its associated context current.
    Window(const Glfw& glfw, std::string title, int width = DEFAULT_WIDTH,
           int height = DEFAULT_HEIGHT);
    ~Window();

    static const int DEFAULT_WIDTH;
    static const int DEFAULT_HEIGHT;

    // Prevent copy, allow move
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = default;
    Window& operator=(Window&&) = default;

    // Runs the main loop until the close flag of the window is set.
    void loop(std::function<void()> body) const;

    // Makes the context of this window the current context
    void make_current() const;

    // Sets callbacks.
    // Must not be called while `loop` is running.
    void on_keydown(Key key, KeyCallback callback);
    void on_scroll(ScrollCallback callback);
    void on_mouse(MouseButtonCallback callback);
    void on_cursor_move(CursorPosCallback callback);
    void on_size_change(FbSizeCallback callback);

    // Toggles vsync on / off.
    // Vsync defaults to on.
    // Returns true if vsync is on after the toggle.
    bool toggle_vsync();

  private:
    struct Impl;
    std::unique_ptr<Impl> impl;
};

#endif
