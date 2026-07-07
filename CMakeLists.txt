cmake_minimum_required(VERSION 3.22)

# 1. Name your plugin project
project(AUDIO_PLUGIN_TEMPLATE VERSION 0.0.1 LANGUAGES C CXX)

# 2. TELL CMAKE WHERE YOUR JUCE FOLDER IS 
# (Double-check this path matches where your downloaded JUCE folder lives)
add_subdirectory("/Users/timursabirov/programing/VSTtest/JUCE" JUCE) 

# 3. Enable the formats you want to build (VST3 and Apple's native AU)
juce_add_plugin(AudioPlugin
    COMPANY_NAME "MyCompany"
    IS_SYNTH FALSE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    JUCE_VST3_CAN_REPLACE_VST2_FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS FALSE
    COPY_PLUGIN_AFTER_BUILD TRUE # Automatically places the plugin in your Mac's system folders
    PLUGIN_MANUFACTURER_CODE "Tmsb"
    PLUGIN_CODE "Vlkn"
    FORMATS VST3 AU Standalone)

# 4. Tell CMake to use your specific uploaded files
target_sources(AudioPlugin PRIVATE
    src/PluginProcessor.h
    src/PluginProcessor.cpp
    src/PluginEditor.h
    src/PluginEditor.cpp)

# 5. Link the standard JUCE audio modules
target_link_libraries(AudioPlugin PRIVATE
    juce::juce_audio_utils
    juce::juce_audio_processors
    juce::juce_gui_extra)

# 6. Set modern C++20 standard
target_compile_features(AudioPlugin PRIVATE cxx_std_20)
add_compile_definitions(JUCE_VST3_CAN_REPLACE_VST2=0)

# 7. Add your asset files to the project
juce_add_binary_data(AudioPluginData SOURCES assets/background.jpg)
target_link_libraries(AudioPlugin PRIVATE AudioPluginData)
target_include_directories(AudioPlugin PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/juce_binarydata_AudioPluginData/JuceLibraryCode")