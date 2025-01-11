#include <AceSorting.h>

const int SAMPLE_COUNT = 10;

class SampleBuffer {
  public:
    SampleBuffer();
    void push(long int sample);
    long int getValue();
  private:
    int index;
    long int samples[SAMPLE_COUNT];
};

SampleBuffer::SampleBuffer() {
  index = 0;
}

void SampleBuffer::push(long int sample) {
  samples[index] = sample;
  index++;
  index %= SAMPLE_COUNT;
}

long int SampleBuffer::getValue() {
  long int sorted_samples[10] = {
    samples[0],
    samples[1],
    samples[2],
    samples[3],
    samples[4],
    samples[5],
    samples[6],
    samples[7],
    samples[8],
    samples[9],
  };
  ace_sorting::bubbleSort(&sorted_samples[0], 10);

  return sorted_samples[4];
}