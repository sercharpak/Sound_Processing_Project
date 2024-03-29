//=======================================================================
/** @file Signal.h
 *  @author Didier Bieler && Sergio Hernandez
 *
 * This file is part of the project of Sound Processing
 *
 * Signal is the core class of the program. It contains the raw sound signals and the
 * Fourier Transform related methods. It can also computes the histogram of the signal
 * and perform the i/o task for a sound file.
 *
 */
//=======================================================================

#ifndef PROJECT_SIGNAL_H
#define PROJECT_SIGNAL_H

#include <complex>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <cmath>
#include "HistogramException.h"
#include "InverseFourierException.h"


#include "AudioFile.h"


/** Class to create and handle a signal.
 */
class Signal{
private:

    /** Samples
     */
    std::vector<double> sample;
    /** Time of the sample.
     */
    std::vector<double> time;
    /** Sample rate of the signal
     */
    double samplerate;

    /** Fourier Transform .
     */
    std::vector<std::complex<double>> fouriertransform;

    /** Frequencies of the Fourier Transform.
     */
    std::vector<double> frequencies;

public:

    /** Default Constructor of the compiler.
     */
    Signal() = default;

    /** Constructor using an AudioFile. The Fourier transform is not calculated.
     *
     * @param audio AudioFile<double> containing an audio file.
     */
    Signal(AudioFile<double> audio);

    /** Constructor using a vector of samples.
     *
     * @param sam std::vector<double> containing the samples.
     */
    Signal(std::vector<double> sam,double samRate=44100);


    /** Default destructor
     */
    ~Signal();


    /** Getter for the vector time.
    *
    * @return std::vector<double> time
    */
    std::vector<double> getTime() const;

    /** Getter for the vector of samples.
     *
     * @return std::vector<double> sample
     */
    std::vector<double> getSamples() const;
    /** Setter for the vector of samples.
     *
     * @param std::vector<double> pSamples
     */
    void setSamples(std::vector<double> pSamples);
    /** Setter for the vector of frequencies.
     *
     * @param std::vector<double> pFrequencies
     */
    void setFrequencies(std::vector<double> pFrequencies);

    /** Getter for the Fourier Transforms.
     *
     * @return std::vector<std::complex<double>> FourierTransform
     */
    std::vector<std::complex<double>> getFourierTransform() const;
    /** Setter for the Fourier Transforms.
     *
     * @param std::vector<std::complex<double>> FourierTransform
     */
    void setFourierTransform(std::vector<std::complex<double>> pFourierTransform);

    /** Getter for the Frequencies.
     *
     * @return std::vector<double> Frequencies
     */
    double getSampleRate() const;

    /** Getter for the sample rate.
     *
     * @return double sample rate
     */
    std::vector<double> getFrequencies() const;

    /** Histogram
     *
     * Compute the histogram of the signal.
     * @param number_bin int which represents the number of bins we want in the histogram.
     * @param file std::ofstream in which we store the histogram and the corresponding bins
     */
    void histogram(int number_bin,std::string fileName) ;
    /** Writer for the Fourier transform into a file (calculate it if not already calculated)
     *
     * Write the Fourier transform into a file (calculate it if not already calculated)
     * @param file std::ofstream in which we store the Fourier transform modulus and the corresponding frequencies.
    */
    void writeFourier(std::string fileName);

    /** Fourier Transform (no file saved)
     *
     * Compute the Fourier transform of the signal.
     * @param min_frequency The minimum frequency where we start to compute the Fourier transform.
     * @param max_frequency The maximum frequency where we stop the computation of the Fourier transform.
    */
    void fouriertransformCalculator();

    /** Save the signal sample and time in a file
     * @param fileName std::string the filename of the file in which we want to store the samples and the time.
     */
    void saveSignal(std::string fileName);

    /** Compute the inverse Fourier Transform.
     *
     * @param fileName  string which gives the name of the file inside we want to store the inverse fourier transform.
     */
    std::vector<double> inversefourierTransform();

    /** Write the signal inside a sound file.
     *
     * @param fileName  string which gives the name of the sound file inside we want to store the signal.
     */
    void writeSound(std::string fileName);



};

/** Concatenation of two signals
     *
     * @param S1 Signal which is the first we want to concatenate.
     * @param S2 Signal which we want to write after S1.
     */

Signal concatenate(const Signal& S1,const Signal& S2);

#endif //PROJECT_SIGNAL_H
