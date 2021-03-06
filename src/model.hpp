#ifndef MODEL_HPP_
#define MODEL_HPP_

#include <cstddef>
#include <memory>
#include <string_view>
#include <vector>

#include "drawable.hpp"

using std::size_t;

class Window;

// Wrapper class for OpenGL data buffers.
// Provides API to draw the buffers.
//
// Note that copies refers to the same data buffers.
// The data buffers are deleted when all copies are destructed.
class Model final : public Drawable {
  public:
    Model(std::string_view path);

    // Draws the model using GL functions
    virtual void draw() const override;

  private:
    struct Impl;
    std::shared_ptr<Impl> impl;
};

// Container of models that provides ability to cycle through the models.
//
// Note that copies refers to the same data.
class ModelList final : public Drawable {
  public:
    ModelList(const std::vector<std::string>& model_paths);

    // Returns a reference to the current model.
    const Model& current() const;

    // Switches current index to the next model.
    void next_model();

    // Switches current index to the previous model.
    void prev_model();

    virtual void draw() const override;

  private:
    struct Impl;
    std::shared_ptr<Impl> impl;
};

#endif
