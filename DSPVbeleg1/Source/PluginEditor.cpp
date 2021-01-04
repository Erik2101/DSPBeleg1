/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DSBVbeleg1AudioProcessorEditor::DSBVbeleg1AudioProcessorEditor (DSBVbeleg1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize(400, 300);

    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    lowCutFilter.setSliderStyle(juce::Slider::LinearBarVertical);
    lowCutFilter.setRange(0.0, 20000.0 , 0.1);
    lowCutFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lowCutFilter.setPopupDisplayEnabled(true, false, this);
    lowCutFilter.setTextValueSuffix(" Hz");
    lowCutFilter.setValue(1.0);
    lowCutFilter.addListener(this);
    addAndMakeVisible(&lowCutFilter);

    highCutFilter.setSliderStyle(juce::Slider::LinearBarVertical);
    highCutFilter.setRange(0.0, 20000.0, 0.1);
    highCutFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    highCutFilter.setPopupDisplayEnabled(true, false, this);
    highCutFilter.setTextValueSuffix(" Hz");
    highCutFilter.setValue(1.0);
    highCutFilter.addListener(this);
    addAndMakeVisible(&highCutFilter);

    lowCutPercent.setSliderStyle(juce::Slider::LinearBarVertical);
    lowCutPercent.setRange(0.0, 100.0, 1.0);
    lowCutPercent.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lowCutPercent.setPopupDisplayEnabled(true, false, this);
    lowCutPercent.setTextValueSuffix(" %");
    lowCutPercent.setValue(0.0);
    lowCutPercent.addListener(this);
    addAndMakeVisible(&lowCutPercent);

    highCutPercent.setSliderStyle(juce::Slider::LinearBarVertical);
    highCutPercent.setRange(0.0, 100.0, 1.0);
    highCutPercent.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    highCutPercent.setPopupDisplayEnabled(true, false, this);
    highCutPercent.setTextValueSuffix(" %");
    highCutPercent.setValue(0.0);
    highCutPercent.addListener(this);
    addAndMakeVisible(&highCutPercent);

    notchFilter.setSliderStyle(juce::Slider::TwoValueVertical);
    notchFilter.setRange(20.0, 7000.0, 0.1);
    notchFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    notchFilter.setPopupDisplayEnabled(true, false, this);
    notchFilter.setTextValueSuffix(" Hz");
    notchFilter.setValue(1.0);
    notchFilter.setMaxValue(7000.0);
    notchFilter.setMinValue(20.0);
    notchFilter.addListener(this);
    addAndMakeVisible(&notchFilter);

    applyButton.setButtonText("Filter anwenden.");
    applyButton.onClick = [this] {
        switch (getSelectedFilter()) {
        case 0: 
            if (lowCutMenu.getSelectedId() == 1) {
                audioProcessor.lowCut1(lowCutFilter.getValue(), audioProcessor.getSampleRate());
            } else {
                audioProcessor.lowCut2(lowCutFilter.getValue(), lowCutPercent.getValue(), audioProcessor.getSampleRate());
            }
            break;
        case 1: 
            if (highCutMenu.getSelectedId() == 1) {
                audioProcessor.highCut1(highCutFilter.getValue(), audioProcessor.getSampleRate());
            } else {
                audioProcessor.highCut2(highCutFilter.getValue(), highCutPercent.getValue(), audioProcessor.getSampleRate());
            }
            break;
        case 2:
            // audioProcessor.notch_coeffs(notchFilter.getMaxValue() - notchFilter.getMinValue(), myFrequenzSlider.getValue(), audioProcessor.getSampleRate());
            break;
        default:
            break;
        }
    };
    addAndMakeVisible(&applyButton);

    lowCutMenu.addItem("1.Ordnung", 1);
    lowCutMenu.addItem("2.Ordnung", 2);
    //lowCutMenu.onChange = [this] { lowCutMenuChanged(); };
    lowCutMenu.setSelectedId(1);
    addAndMakeVisible(&lowCutMenu);

    highCutMenu.addItem("1.Ordnung", 1);
    highCutMenu.addItem("2.Ordnung", 2);
    //highCutMenu.onChange = [this] { highCutMenuChanged(); };
    highCutMenu.setSelectedId(1);
    addAndMakeVisible(&highCutMenu);

    addAndMakeVisible(lowCutButton);
    addAndMakeVisible(highCutButton);
    addAndMakeVisible(notchButton);

    lowCutButton.setButtonText("Hochpassfilter");
    highCutButton.setButtonText("Tiefpassfilter");
    notchButton.setButtonText("Notchfilter");

    lowCutButton.onClick = [this] 
    { 
        normalToggleState(&lowCutButton, "Hochpassfilter");
        setSelectedFilter(0);
     };

    highCutButton.onClick = [this] 
    { 
        normalToggleState(&highCutButton, "Tiefpassfilter");
        setSelectedFilter(1);
    };

    notchButton.onClick = [this] 
    {
        normalToggleState(&notchButton, "Notchfilter"); 
        setSelectedFilter(2);
    };

    lowCutButton.setRadioGroupId(FilterButtons);
    highCutButton.setRadioGroupId(FilterButtons);
    notchButton.setRadioGroupId(FilterButtons);
}

DSBVbeleg1AudioProcessorEditor::~DSBVbeleg1AudioProcessorEditor()
{
}

//==============================================================================
void DSBVbeleg1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

void DSBVbeleg1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    lowCutButton.setBounds(10, 0, getWidth(), 30);
    highCutButton.setBounds(160, 0, getWidth(), 30);
    notchButton.setBounds(300, 0, getWidth(), 30);

    lowCutMenu.setBounds(10, 40, getWidth() - 300, 20);
    highCutMenu.setBounds(160, 40, getWidth() - 300, 20);

    lowCutFilter.setBounds(40, 80, 20, getHeight() - 120);
    lowCutPercent.setBounds(80, 80, 20, getHeight() - 120);

    highCutFilter.setBounds(190, 80, 20, getHeight() - 120);
    highCutPercent.setBounds(230, 80, 20, getHeight() - 120);

    notchFilter.setBounds(340, 80, 20, getHeight() - 120);

    applyButton.setBounds(0, getHeight() - 25, getWidth(), 25);


}

void DSBVbeleg1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // audioProcessor.noteOnVel = lowCutFilter.getValue();
}



