//
// Created by shernand on 11/30/17.
//

#include "AudioFile.h"
#include "Signal.h"
#include "StandardFilter.h"
//#include "MeanFilter.h"
#include <fstream>
#include <vector>
#include <cmath>
#include <algorithm>

int main(int argc, char* argv[]) {
    try {
        Signal Sign("../test-audio/wav_mono_16bit_44100.wav");
        std::ofstream write_hist("Histogram.dat");
        Histogram(Sign, 50, write_hist);
        write_hist.close();
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }
    //TODO Testing a filter
    //SDHC: to plot in gnuplot
    //plot "cmake-build-debug/Output_Filter.dat" using 1:2 title "Original", "cmake-build-debug/Output_Filter.dat" using 1:3 title "Filtered"
    try {
        Signal Sign("../test-audio/wav_mono_16bit_44100.wav");
        int channel = 0;
        std::vector<double> signalToFilter = Sign.getAudioFile().samples[channel];
        std::cout << signalToFilter.size();
        int filterSize = 5;
        StandardFilter<double> meanFilter = StandardFilter<double>(filterSize);
        std::vector<double> maskMean = std::vector<double>(filterSize);
        std::for_each(maskMean.begin(), maskMean.end(),
                      [filterSize](double &x) { x = (1.0/filterSize); }); //Fills the mask
        std::for_each(maskMean.begin(), maskMean.end(),
                      [](double x) { std::cout << x << std::endl; });
        meanFilter.setMask(maskMean);
        std::vector<double> signalFiltered =meanFilter.apply(signalToFilter);

        std::cout << signalFiltered.size();

        //MeanFilter<double> myMean = MeanFilter<double>(filterSize);




        std::ofstream write_output("Output_Filter.dat");
        std::vector<double> time;
        int sampleRate = Sign.getAudioFile().getSampleRate();
        int numSamples = Sign.getAudioFile().getNumSamplesPerChannel();
        double step((numSamples /(sampleRate*1.0))/numSamples);

        for (int i = 0; i<numSamples;++i){
            time.push_back(i*step);
        }
        std::cout<<time.size()<<std::endl;
        for (int i = 0; i < numSamples; i++)
        {
            double currentSample = Sign.getAudioFile().samples[channel][i];
            write_output<<time[i]<<" ";
            write_output<<currentSample<<" ";
            write_output<<signalFiltered[i]<<std::endl;

        }

        write_output.close();
    }
    catch(const std::runtime_error &e){
        std::cout << e.what() <<std::endl;
        return 1;
    }

    return 0;
}