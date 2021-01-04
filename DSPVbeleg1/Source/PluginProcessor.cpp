/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
using namespace juce;

//==============================================================================
DSBVbeleg1AudioProcessor::DSBVbeleg1AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DSBVbeleg1AudioProcessor::~DSBVbeleg1AudioProcessor()
{
}

//==============================================================================
const juce::String DSBVbeleg1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DSBVbeleg1AudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DSBVbeleg1AudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DSBVbeleg1AudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DSBVbeleg1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DSBVbeleg1AudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DSBVbeleg1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void DSBVbeleg1AudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DSBVbeleg1AudioProcessor::getProgramName (int index)
{
    return {};
}

void DSBVbeleg1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DSBVbeleg1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void DSBVbeleg1AudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DSBVbeleg1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DSBVbeleg1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    for (int channels = 0; channels < buffer.getNumChannels(); ++channels) {

        const float* inputData = buffer.getReadPointer(channels);

        float* outputData = buffer.getWritePointer(channels);

        int bufferSize = buffer.getNumSamples();
        float sampleRate = this->getSampleRate();
        double filter = 0.0;
        for (int sample = 0; sample < bufferSize; ++sample) {
            if (sample > 2) {
                filter = my_coeffs.a0 * inputData[sample] + my_coeffs.a1 * inputData[sample - 1] + my_coeffs.a2 * inputData[sample - 2] - my_coeffs.b0 * inputData[sample - 1] - my_coeffs.b1 * inputData[sample - 2];
            }
            outputData[sample] = filter;
        }
    }
}

//==============================================================================
bool DSBVbeleg1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DSBVbeleg1AudioProcessor::createEditor()
{
    return new DSBVbeleg1AudioProcessorEditor (*this);
}

//==============================================================================
void DSBVbeleg1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DSBVbeleg1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DSBVbeleg1AudioProcessor();
}
