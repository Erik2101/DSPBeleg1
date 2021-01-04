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
    lowCutFilter.setRange(0.0, 127.0, 1.0);
    lowCutFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    lowCutFilter.setPopupDisplayEnabled(true, false, this);
    lowCutFilter.setTextValueSuffix(" Hz");
    lowCutFilter.setValue(1.0);
    lowCutFilter.addListener(this);
    addAndMakeVisible(&lowCutFilter);

    highCutFilter.setSliderStyle(juce::Slider::LinearBarVertical);
    highCutFilter.setRange(0.0, 127.0, 1.0);
    highCutFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    highCutFilter.setPopupDisplayEnabled(true, false, this);
    highCutFilter.setTextValueSuffix(" Hz");
    highCutFilter.setValue(1.0);
    highCutFilter.addListener(this);
    addAndMakeVisible(&highCutFilter);

    percentChoiceOne.setSliderStyle(juce::Slider::LinearBarVertical);
    percentChoiceOne.setRange(0.0, 100.0, 1.0);
    percentChoiceOne.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    percentChoiceOne.setPopupDisplayEnabled(true, false, this);
    percentChoiceOne.setTextValueSuffix(" %");
    percentChoiceOne.setValue(0.0);
    percentChoiceOne.addListener(this);
    addAndMakeVisible(&percentChoiceOne);

    percentChoiceTwo.setSliderStyle(juce::Slider::LinearBarVertical);
    percentChoiceTwo.setRange(0.0, 100.0, 1.0);
    percentChoiceTwo.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    percentChoiceTwo.setPopupDisplayEnabled(true, false, this);
    percentChoiceTwo.setTextValueSuffix(" %");
    percentChoiceTwo.setValue(0.0);
    percentChoiceTwo.addListener(this);
    addAndMakeVisible(&percentChoiceTwo);

    notchFilter.setSliderStyle(juce::Slider::LinearBarVertical);
    notchFilter.setRange(0.0, 127.0, 1.0);
    notchFilter.setTextBoxStyle(juce::Slider::NoTextBox, false, 90, 0);
    notchFilter.setPopupDisplayEnabled(true, false, this);
    notchFilter.setTextValueSuffix(" Hz");
    notchFilter.setValue(1.0);
    notchFilter.addListener(this);
    addAndMakeVisible(&notchFilter);

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
    percentChoiceOne.setBounds(265,80,20,getHeight() - 120);
    percentChoiceTwo.setBounds(115, 80, 20, getHeight() - 120);
    notchFilter.setBounds(340, 80, 20, getHeight() - 120);
}

void DSBVbeleg1AudioProcessorEditor::sliderValueChanged(juce::Slider* slider)
{
    // audioProcessor.noteOnVel = lowCutFilter.getValue();
}



