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

    notchFilter.setSliderStyle(juce::Slider::LinearBarVertical);
    notchFilter.setRange(0.0, 127.0, 1.0);
    notchFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    notchFilter.setPopupDisplayEnabled(true, false, this);
    notchFilter.setTextValueSuffix(" Hz");
    notchFilter.setValue(1.0);
    notchFilter.addListener(this);
    addAndMakeVisible(&notchFilter);

    applyButton.setButtonText("Filter anwenden.");
    applyButton.onClick = [this] {
        audioProcessor.lpf1_coeffs(highCutFilter.getValue(), audioProcessor.getSampleRate());
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
}

DSBVbeleg1AudioProcessorEditor::~DSBVbeleg1AudioProcessorEditor()
{
}

//==============================================================================
void DSBVbeleg1AudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));

    g.setColour(juce::Colours::white);
    g.setFont(15.0f);
    g.drawFittedText("Hochpassfilter", 10, 0, getWidth(), 30, juce::Justification::centredLeft, 1);
    g.drawFittedText("Tiefpassfilter", 160, 0, getWidth(), 30, juce::Justification::centredLeft, 1);
    g.drawFittedText("Notchfilter", 310, 0, getWidth(), 30, juce::Justification::centredLeft, 1);
}

void DSBVbeleg1AudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    lowCutMenu.setBounds(10, 40, getWidth() - 300, 20);
    highCutMenu.setBounds(160, 40, getWidth() - 300, 20);
    lowCutFilter.setBounds(40, 80, 20, getHeight() - 120);
    highCutFilter.setBounds(190, 80, 20, getHeight() - 120);
    lowCutPercent.setBounds(80, 80, 20, getHeight() - 120);
    highCutPercent.setBounds(230, 80, 20, getHeight() - 120);
    notchFilter.setBounds(340, 80, 20, getHeight() - 120);
    applyButton.setBounds(0, getHeight() - 25, getWidth(), 25);
}

void DSBVbeleg1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // audioProcessor.noteOnVel = lowCutFilter.getValue();
}



