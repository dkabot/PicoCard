#ifndef PICOCARD_IMAGES_IMAGE_H_
#define PICOCARD_IMAGES_IMAGE_H_
#include <cstdint>

namespace picocard {
// Represents an image made up of 16-bit pixels (myColours, likely)
// with a maximum size of 255*255
class Image {
  public:
    Image(const uint8_t size_x, const uint8_t size_y);
    virtual uint16_t& operator[](int index) = 0; // Index operator e.g. Image[i]
    virtual const uint16_t& operator[](int index) const = 0; // Unmodifiable
    uint8_t get_size_x() const;
    uint8_t get_size_y() const;

  private:
    const uint8_t size_x_;
    const uint8_t size_y_;
};

// Implementation of straightforward constructor and getters
inline Image::Image(const uint8_t size_x, const uint8_t size_y)
  : size_x_(size_x), size_y_(size_y) {}

inline uint8_t Image::get_size_x() const {
  return size_x_;
}
inline uint8_t Image::get_size_y() const {
  return size_y_;
}
} // namespace picocard
#endif // PICOCARD_IMAGES_UI_IMAGE_H_