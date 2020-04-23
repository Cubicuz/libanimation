#include "animations.h"

void Animations::Static::rainbow(
    std::function<void(uint32_t, uint8_t, uint8_t, uint8_t)> setPixelColor,
    uint32_t ledCount) {
  for (uint32_t i = 0; i < ledCount; i++) {
    setPixelColor(i, Helper::wheel(i, ledCount),
                  Helper::wheel((i + ledCount / 3) % ledCount, ledCount),
                  Helper::wheel((i + ledCount * 2 / 3) % ledCount, ledCount));
  }
}

void Animations::Static::rainbow(uint8_t *memory, uint32_t ledCount) {
  for (uint32_t i = 0; i < ledCount; i++) {
    memory[i * 3] = Helper::wheel(i, ledCount);
    memory[i * 3 + 1] = Helper::wheel((i + ledCount / 3) % ledCount, ledCount);
    memory[i * 3 + 2] =
        Helper::wheel((i + ledCount * 2 / 3) % ledCount, ledCount);
  }
}

void Animations::Dynamic::rain(uint8_t *memory, uint32_t ledCount,
                               uint8_t dropRadius, uint32_t dropCountDivisor,
                               uint8_t reduction) {
  // evaporate
  for (uint32_t i = 0; i < ledCount; i++) {
    if (memory[i] > reduction) {
      memory[i] -= reduction;
    } else {
      memory[i] = 0;
    }
  }

  // new drops
  uint32_t drops = random(0, max(1U, ledCount / dropCountDivisor) * 33) >> 5;
  for (uint32_t i = 0; i < drops; i++) {
    uint32_t position = random(dropRadius - 1, ledCount - dropRadius + 1);
    uint8_t increment = 255;
    memory[position] = increment;
    for (uint8_t j = 1; j < dropRadius; j++) {
      increment /= 2;
        memory[position + j] = min(255, memory[position + j] + increment);
        memory[position - j] = min(255, memory[position - j] + increment);
    }
  }
}

void Animations::Dynamic::rainbow(
    std::function<void(uint32_t, uint8_t, uint8_t, uint8_t)> setPixelColor,
    uint32_t ledCount, uint32_t &progress, uint32_t resolutionFactor) {

  uint32_t resolution = ledCount * resolutionFactor;
  progress = (progress + 1) % resolution;
  for (uint32_t i = 0; i < ledCount; i++) {
    uint32_t index = i * resolutionFactor + progress;
    uint32_t offset = resolution / 3;
    uint8_t r = Helper::wheel(index % resolution, resolution);
    uint8_t g = Helper::wheel((index + offset) % resolution, resolution);
    uint8_t b = Helper::wheel((index + 2 * offset) % resolution, resolution);
    setPixelColor(i, r, g, b);
  }
}

uint8_t Animations::Helper::wheel(uint32_t x, uint32_t resolution) {
  // function looks like ／￣￣＼＿＿
  // is splittet in 4 parts (rising 0, high 1-2, falling 3, low 4-5)

  if (x * 6 < resolution)            // x < 1/6 * resolution
  {                                  // rising
    return 255 * 6 * x / resolution; // 255 * x / (resolution / 6)
  } else if (x * 2 < 1 * resolution) // x < 3/6 * resolution
  {                                  // high
    return 255;
  } else if (x * 3 < 2 * resolution) // x < 4/6 * resolution
  {                                  // falling
    return (4 * 255 - 6 * x * 255 / resolution);
  } else { // low
    return 0;
  }
}
