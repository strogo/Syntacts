#pragma once

#include <Syntacts/Config.hpp>
#include <Syntacts/Generator.hpp>
#include <Syntacts/Tween.hpp>
#include <Syntacts/Oscillator.hpp>
#include <functional>
#include <map>
#include <utility>

namespace tact
{
/// Base Envelope 
class SYNTACTS_API Envelope : public Generator{
public:
    Envelope(float duration = 1.0f);

    /// Gets the duration of an Envelope
    virtual float getDuration() const;

protected:

    float m_duration;
};

/// Base Envelope
class SYNTACTS_API KeyedEnvelope : public Envelope {
public:

    /// Constucts Envelope with initial amplitude
    KeyedEnvelope(float amplitude0 = 0.0f);

    /// Adds a new amplitude at time t seconds. Uses tween to interpolate from previous amplitude.
    void addKey(float t, float amplitude, TweenFunc tween = Tween::Linear);

    float getDuration() const override;

protected:

    virtual float onSample(float t) override;

protected:

    std::map<float, std::pair<float, TweenFunc>> m_keys;
    
};


/// An object which gives a Cue a duration and/or shape
class SYNTACTS_API BasicEnvelope : public KeyedEnvelope {
public:

    /// Constructs an Eveloope with a specified duration
    BasicEnvelope(float duration = 1.0f, float amplitude = 1.0f);

    /// Gets the normalized amlitude of the Envelope
    float getAmplitude() const;

};


/// Attack-Sustain-Release Envelope
class SYNTACTS_API ASR : public KeyedEnvelope {
public:

    /// Constructs ASR Envelope with specified attack, sustain, and release times
    ASR(float attackTime, float sustainTime, float releaseTime, float attackAmlitude = 1.0f, 
        TweenFunc attackTween = Tween::Linear, TweenFunc releaseTween = Tween::Linear);

};


/// Attack-Decay-Sustain-Release Envelope
class SYNTACTS_API ADSR : public KeyedEnvelope {
public:

    /// Constructs ASR Envelope with specified attack, sustain, and release times
    ADSR(float attackTime, float decayTime, float sustainTime, float releaseTime, float attackAmplitude = 1.0f, float decayAplitude = 0.5f, 
         TweenFunc attackTween = Tween::Linear, TweenFunc decayTween = Tween::Linear, TweenFunc releaseTween = Tween::Linear);

};

/// An object which gives a Cue a duration and/or shape
class SYNTACTS_API OscillatingEnvelope : public Envelope {
public:

    /// Constructs an Envelope with a specified duration, positive oscillator type and frequency
    OscillatingEnvelope(float duration , float amplitude, std::shared_ptr<Oscillator> osc);

protected:

    virtual float onSample(float t) override;

    std::shared_ptr<Oscillator> m_osc;
    float m_amplitude;
};

} // namespace tact