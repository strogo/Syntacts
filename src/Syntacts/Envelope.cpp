#include <Syntacts/Envelope.hpp>
#include <Syntacts/Tween.hpp>
#include <Syntacts/Oscillator.hpp>
#include "Util/Util.hpp"
#include <functional>

namespace tact {

EnvelopeBase::EnvelopeBase(float duration) :
    m_duration(duration)
{
    
}

float EnvelopeBase::sample(float t) const {
    return t > m_duration ? 0.0f : 1.0f;
}

float EnvelopeBase::getDuration() const {
    return m_duration;
}

Envelope::Envelope(float duration, float amplitude) :
    EnvelopeBase(duration), m_amplitude(amplitude)
{ }

float Envelope::sample(float t) const {
    return t > m_duration ? 0.0f : m_amplitude;
}

KeyedEnvelope::KeyedEnvelope(float amplitude0) :
    EnvelopeBase()
{
   addKey(0.0f, amplitude0, create<Tween::Linear>());
}

void KeyedEnvelope::addKey(float t, float amplitude, TweenFunc tween) {
    m_keys[t] = std::make_pair(amplitude, tween);
}

float KeyedEnvelope::getDuration() const {
    return m_keys.rbegin()->first;
}

float KeyedEnvelope::sample(float t) const {
    if (t > getDuration())
        return 0.0f;
    auto b = m_keys.lower_bound(t);
    if (b->first == t)
        return b->second.first;
    auto a = std::prev(b);
    t = (t - a->first) / (b->first - a->first);
    return b->second.second->tween(a->second.first, b->second.first, t);    
}




ASR::ASR(float attackTime, float sustainTime, float releaseTime, float attackAmplitude, TweenFunc attackTween, TweenFunc releaseTween) :
    KeyedEnvelope(0.0f)
{
    addKey(attackTime, attackAmplitude, attackTween);
    addKey(attackTime + sustainTime, attackAmplitude, create<Tween::Instant>());
    addKey(attackTime + sustainTime + releaseTime, 0.0f, releaseTween);
}


ADSR::ADSR(float attackTime, float decayTime, float sustainTime, float releaseTime, float attackAmplitude, float decayAmplitude, TweenFunc attackTween, TweenFunc decayTween, TweenFunc releaseTween) :
    KeyedEnvelope(0.0f)
{
    addKey(attackTime, attackAmplitude, attackTween);
    addKey(attackTime + decayTime, decayAmplitude, decayTween);
    addKey(attackTime + decayTime + sustainTime, decayAmplitude, create<Tween::Instant>());
    addKey(attackTime + decayTime + sustainTime + releaseTime, 0.0f, releaseTween);
}

OscillatingEnvelope::OscillatingEnvelope(float duration , float amplitude , Ptr<OscillatorBase> osc) :
    EnvelopeBase(duration), m_amplitude(amplitude), m_osc(std::move(osc))
{
    
}

float OscillatingEnvelope::sample(float t) const {
    if (t > getDuration())
        return 0.0f;
    float value = m_osc->sample(t);  
    value = remap(value, -1, 1 , 0 , m_amplitude);
    return value;
}

} // namespace tact