/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include <math.h>

//==============================================================================
/**
*/
class DSBVbeleg1AudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================

    struct coeffs {
        double a0;
        double a1;
        double a2;
        double b0;
        double b1;
    };
    coeffs my_coeffs;

    const double pi = 3.14159265359;

    DSBVbeleg1AudioProcessor();
    ~DSBVbeleg1AudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    void hpf1_coeffs(double cuttOff, double sampleRate) {
        double th = 2.0 * pi * cuttOff / sampleRate;
        double g = cos(th) / (1.0 + sin(th));
        my_coeffs.a0 = (1.0 + g) / 2.0;
        my_coeffs.a1 = -((1.0 + g) / 2.0);
        my_coeffs.a2 = 0.0;
        my_coeffs.b0 = -g;
        my_coeffs.b1 = 0.0;
    }
    void hpf2_coeffs(double Q, double cuttOff, double sampleRate) {

        double w = 2.0 * pi * cuttOff / sampleRate;
        double d = 1.0 / Q;
        double b = 0.5 * (1.0 - (d / 2) * sin(w)) / (1.0 + (d / 2.0) * sin(w));
        double g = (0.5 + b) * cos(w);
        my_coeffs.a0 = (0.5 + b + g) / 2.0;
        my_coeffs.a1 = -(0.5 + b + g);
        my_coeffs.a2 = my_coeffs.a0;
        my_coeffs.b0 = 2.0 * g;
        my_coeffs.b1 = 2.0 * b;
    };
    void lpf1_coeffs(double cuttOff, double sampleRate) {
        double th = 2.0 * pi * cuttOff / sampleRate;
        double g = cos(th) / (1.0 + sin(th));
        my_coeffs.a0 = (1.0 - g) / 2.0;
        my_coeffs.a1 = (1.0 - g) / 2.0;
        my_coeffs.a2 = 0.0;
        my_coeffs.b0 = -g;
        my_coeffs.b1 = 0.0;
    };
    void lpf2_coeffs(double Q, double cuttOff, double sampleRate) {
        double w = 2.0 * pi * cuttOff / sampleRate;
        double d = 1.0 / Q;
        double b = 0.5 * (1.0 - (d / 2) * sin(w)) / (1.0 + (d / 2.0) * sin(w));
        double g = (0.5 + b) * cos(w);
        my_coeffs.a0 = (0.5 + b - g) / 2.0;
        my_coeffs.a1 = 0.5 + b - g;
        my_coeffs.a2 = my_coeffs.a0;
        my_coeffs.b0 = -2.0 * g;
        my_coeffs.b1 = 2.0 * b;
    };
    void notch_coeffs(double bandWidth, double cuttOff, double sampleRate) {
        double th = (1 - tan(pi * bandWidth / sampleRate) / (1 - tan(pi * bandWidth / sampleRate)));
        double g = -cos(2 * pi * cuttOff / sampleRate);
        my_coeffs.a0 = th;
        my_coeffs.a1 = g * (1 + th);
        my_coeffs.a2 = 1;
        my_coeffs.b0 = my_coeffs.a1;
        my_coeffs.b1 = th;
    };

    void setSliderValue(float value) {
        SliderValue = value;
    }

private:

    float SliderValue;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DSBVbeleg1AudioProcessor)
};
