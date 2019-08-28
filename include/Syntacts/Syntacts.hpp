#pragma once

#include <Syntacts/Config.hpp>
#include <Syntacts/Generator.hpp>
#include <Syntacts/Oscillator.hpp>
#include <Syntacts/Envelope.hpp>
#include <Syntacts/Cue.hpp>
#include <Syntacts/AudioFile.hpp>
#include <string>

namespace tact {  

/// Struct holding ASIO device information
struct SYNTACTS_API DeviceInfo {
    int index;         ///< device index
    std::string name;  ///< device name
    int maxChannels;   ///< maximum number of output channels
};    

/// Return errors
enum SyntactsError : int {
    SyntactsError_NoError             =  0,
    SyntactsError_InvalidDevice       = -1,
    SyntactsError_NotInitialized      = -2,
    SyntactsError_AlreadyIntialized   = -3,
    SyntactsError_InvalidChannel      = -4,
    SyntactsError_InvalidChannelCount = -5,
    SyntactsError_NoWaveform          = -6,
    SyntactsError_AudioFileBufferFail = -7,
    SyntactsError_AudioFileSaveFail   = -8
};

#ifndef SYNTACTS_ANSI_C    

//==============================================================================
// C++11 INTERFACE
//==============================================================================

/// Intializes Syntacts Library with default device and output max channels  
SYNTACTS_API int initialize();

/// Initializes Syntacts Library with a specified number of channels
SYNTACTS_API int initialize(int channelCount);

/// Initializes Syntacts Library with a specified number of channels and specific device number
SYNTACTS_API int initialize(int device, int channelCount);

/// Finalizes Syntacts Libary
SYNTACTS_API int finalize();

/// Get the default device
SYNTACTS_API DeviceInfo getDefaultDevice();

/// Get the current device
SYNTACTS_API DeviceInfo getCurrentDevice();

/// Gets list of avaialable ASIO devices
SYNTACTS_API std::vector<DeviceInfo> getAvailableDevices();

/// Plays a Cue on a specified channel asynchronously
SYNTACTS_API int play(int channel, std::shared_ptr<Cue> cue);  

/// Plays a Cue on a specified channel asynchronously
SYNTACTS_API int play(int channel,   // channel              [0 to N]
                 int oscType,   // oscillator type      [0=none, 1=sin, 2=sqr, 3=saw, 4=tri]
                 float oscFreq, // oscillator frequency [Hz]
                 int modType,   // modulator type       [0=none, 1=sin, 2=sqr, 3=saw, 4=tri]
                 float modFreq, // modulator frequency  [Hz]
                 float amp,     // envelope amplitude  [0 to 1]
                 float A,       // attack time          [s]
                 float S,       // sustain time         [s]
                 float R);      // release time         [s]

/// Plays a Cue on all channels
SYNTACTS_API int playAll(std::shared_ptr<Cue> cue);

/// Stops running cue on a single channel
SYNTACTS_API int stop(int channel);

/// Stops all running cues
SYNTACTS_API int stopAll();

/// Saves a Cue to an audio file
SYNTACTS_API int save(std::shared_ptr<Cue> cue, std::string filePath, AudioFileFormat format = AudioFileFormat::Wave);

#else

//==============================================================================
// ANSI C INTEFACE (FOR DLL BASED BINDINGS)
//==============================================================================

SYNTACTS_API int initialize(int channelCount);
SYNTACTS_API int initialize(int device, int channelCount);
SYNTACTS_API DeviceInfo getDefaultDevice();
SYNTACTS_API DeviceInfo getCurrentDevice();
SYNTACTS_API std::vector<DeviceInfo> getAvailableDevices();

extern "C" {

SYNTACTS_API int initialize();
SYNTACTS_API int initializeChannels(int channelCount);
SYNTACTS_API int initializeCustom(int device, int channelCount);
SYNTACTS_API int finalize();

SYNTACTS_API int play(int channel,   // channel              [0 to N]
                 int oscType,   // oscillator type      [0=none, 1=sin, 2=sqr, 3=saw, 4=tri]
                 float oscFreq, // oscillator frequency [Hz]
                 float oscAmp,  // oscillator amplitude [0 to 1]
                 int modType,   // modulator type       [0=none, 1=sin, 2=sqr, 3=saw, 4=tri]
                 float modFreq, // modulator frequency  [Hz]
                 float modAmp,  // modulator amplitude  [0 to 1]
                 float A,       // attack time          [s]
                 float S,       // sustain time         [s]
                 float R);      // release time         [s]

SYNTACTS_API int stop(int channel);
SYNTACTS_API int stopAll();

}; // extern "C"

#endif // SYNTACTS_ANSI_C

} // namespace tact