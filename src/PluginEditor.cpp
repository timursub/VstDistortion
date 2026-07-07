#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "BinaryData.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    volumeSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    volumeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    volumeSlider.setRange (0.5f, 15.0f, 0.01f);
    volumeSlider.setValue (audioProcessor.DriveAmount);
    volumeSlider.addListener (this);
    addAndMakeVisible (volumeSlider);
    
    masterSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    masterSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    masterSlider.setRange (0.0f, 1.0f, 0.01f);
    masterSlider.setValue (audioProcessor.masterVolume);
    masterSlider.addListener (this);
    addAndMakeVisible (masterSlider);

    backgroundImage = juce::ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);

    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    volumeSlider.removeListener (this);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
   g.drawImageWithin (backgroundImage, 
                       0, 0, getWidth(), getHeight(), 
                       juce::RectanglePlacement::stretchToFit);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    g.drawFittedText ("piska!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    volumeSlider.setBounds (75, 100, 100, 100);
    masterSlider.setBounds (225, 100, 100, 100);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &volumeSlider)
    {
        audioProcessor.DriveAmount = volumeSlider.getValue();
    }
    else if (slider == &masterSlider)
    {
        audioProcessor.masterVolume = volumeSlider.getValue();
    }
}
