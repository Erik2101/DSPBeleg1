/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DSBVbeleg1AudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Slider::Listener
{
public:
    DSBVbeleg1AudioProcessorEditor (DSBVbeleg1AudioProcessor&);
    ~DSBVbeleg1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DSBVbeleg1AudioProcessor& audioProcessor;

    void sliderValueChanged(juce::Slider* slider) override;

    juce::Slider lowCutFilter;
    juce::Slider highCutFilter;
    juce::Slider notchFilter;
    juce::Slider percentChoiceOne;
    juce::Slider percentChoiceTwo;
    juce::ComboBox lowCutMenu;
    juce::ComboBox highCutMenu;
    juce::TextButton applyButton;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DSBVbeleg1AudioProcessorEditor)
};
