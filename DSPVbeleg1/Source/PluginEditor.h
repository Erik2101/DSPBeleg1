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
    enum RadioButtonIds
    {
        FilterButtons = 1001,
    };

    void paint (juce::Graphics&) override;
    void resized() override;

    void updateToggleState(juce::Button* button, juce::String name)
    {
        auto state = button->getToggleState();
        juce::String stateString = state ? "ON" : "OFF";

        juce::Logger::outputDebugString(name + " Button changed to " + stateString);
    }


    void normalToggleState(juce::Button* button, juce::String name)
    {
        auto state = button->getToggleState();
        juce::String stateString = state ? "ON" : "OFF";

        juce::Logger::outputDebugString(name + " Button changed to " + stateString);
        button->setButtonText(name);
    }
    
    int getSelectedFilter() {
        return selectedFilter;
    }

    void setSelectedFilter(int value) {
        selectedFilter = value;
    }

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DSBVbeleg1AudioProcessor& audioProcessor;

    void sliderValueChanged(juce::Slider* slider) override;

    juce::Slider lowCutFilter;
    juce::Slider highCutFilter;
    juce::Slider notchFilter;
    juce::Slider lowCutPercent;
    juce::Slider highCutPercent;
    juce::ComboBox lowCutMenu;
    juce::ComboBox highCutMenu;
    juce::TextButton applyButton;
    juce::ToggleButton lowCutButton;
    juce::ToggleButton highCutButton;
    juce::ToggleButton notchButton;

    int selectedFilter;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DSBVbeleg1AudioProcessorEditor)
};
