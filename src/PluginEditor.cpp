#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    volumeSlider.setSliderStyle (juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    
    // 2. Hide the raw number text box under it to keep it clean
    volumeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 0, 0);
    
    // 3. Match our 0.0 to 1.0 audio volume limits
    volumeSlider.setRange (0.0f, 1.0f, 0.01f);
    
    // 4. Set the initial knob position to match the brain's current volume (0.5f)
    volumeSlider.setValue (audioProcessor.Volume);

    // 5. Tell the knob to report to this file when a user drags it
    volumeSlider.addListener (this);

    // 6. Make it visible on the screen
    addAndMakeVisible (volumeSlider);

    // Set the overall plugin window size (Width, Height in pixels)
    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    volumeSlider.removeListener (this);
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("piska!", getLocalBounds(), juce::Justification::centred, 1);
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    volumeSlider.setBounds (150, 100, 100, 100);
}

void AudioPluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    // Check if the slider that moved is our volume slider
    if (slider == &volumeSlider)
    {
        // Change the brain's volume variable to match the knob's position!
        audioProcessor.Volume = volumeSlider.getValue();
    }
}
