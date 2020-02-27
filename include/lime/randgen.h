#pragma once

/*
  Random number generators.
  Create using static method makeRandGen.
  Legal names are (replacing "<arg>" with double value):
  - constant(<val>)                Constant value
  - uniform01                      Uniform val between 0 and 1
  - uniform(<minval>,<maxval>)     Uniform val between min and max
  - uniform0n-1(<n>)               Uniform betwen 0 and n-1 (integer)
  - normal01                       Standard Normal
  - normal(<mean>,<stddev>)        Normal with given mean and std dev
  - lognormal(<mean>,<stddev>)     LogNormal with given mean and std dev
  - truncnormal(<mean>,<stddev>,<minval>,<maxval>)
                                   Truncated Normal with given mean and std dev
  - stdexp                         Standard Exponential
  - exp(<mean>)                    Exponential with given mean
*/

#include <iostream>
#include <cfloat>
#include <memory>

#include "lime/rand.h"
#include "lime/displayable.h"

namespace lime {

    class RandGen;
    using RandGenPtr = std::shared_ptr<RandGen>;

    /** Class for generating pseudo-random numbers in various distributions. */
    class RandGen : public Rand
    {
    public:
        /** Constructor.
            @param seed seed for the pseud-random number generator.
         */
        RandGen (std::string name, int seed = 0) : Rand(seed), name_(name) {}

        virtual double draw() = 0;
        std::string name() const {return name_;}

        static RandGenPtr makeRandGen (
            std::string name, int seed = 0
        );

        void display(std::ostream& os) const override
        {
            os << name_;
        }

    private:
        std::string name_;
    };
    
    class RandUniform01 : public RandGen
    {
    public:
        RandUniform01 (int seed) :
            RandGen (std::string("RandUniform01"), seed)
        {}

        double draw() override {return uniform01();}
    };

    class RandConstant : public RandGen
    {
    public:
        RandConstant (double val, int seed) :
            RandGen (std::string("RandConstant"), seed),
            val_(val)
        {}

        double draw() override {return val_;}

    private:
        double val_;
    };

    class RandUniform : public RandGen
    {
    public:
        RandUniform (
            double minVal, double maxVal, int seed
        ) :
            RandGen (std::string("RandUniform"), seed),
            minVal_(minVal),
            maxVal_(maxVal)
        {}

        double draw() override {
            return minVal_ + uniform01() * (maxVal_ - minVal_);
        }

    private:
        double minVal_;
        double maxVal_;
    };

    class RandUniform0n_1 : public RandGen
    {
    public:
        RandUniform0n_1 (int n, int seed) :
            RandGen (std::string("RandUniform0n-1"), seed), n_(n)
        {}

        double draw() override {return (double) uniform0n_1(n_);}

    private:
        int n_;
    };

    class RandNormal01 : public RandGen
    {
    public:
        RandNormal01 (int seed) :
            RandGen (std::string("RandNormal01"), seed) {}

        double draw() override {return normal01();}
    };

    class RandNormal : public RandGen
    {
    public:
        RandNormal (double mean, double sd, int seed) :
            RandGen (std::string("RandNormal"), seed),
            mean_(mean),
            sd_(sd)
        {}

        double draw() override {
            return normal (mean_, sd_);
        }

    private:
        double mean_;
        double sd_;
    };

    class RandLogNormal : public RandGen
    {
    public:
        RandLogNormal (double mean, double sd, int seed) :
            RandGen (std::string("RandLogNormal"), seed),
            mean_(mean),
            sd_(sd)
        {}

        double draw() override {
            return logNormal (mean_, sd_);
        }

    private:
        double mean_;
        double sd_;
    };

    class RandTruncNormal : public RandGen
    {
    public:
        RandTruncNormal (
            double mean, double sd, double minVal, double maxVal,
            int seed
        ) :
            RandGen (std::string("RandTrunNormal"), seed),
            mean_(mean),
            sd_(sd),
            minVal_(minVal),
            maxVal_(maxVal)
        {}

        double draw() override {
            double val = mean_ + normal01() * sd_;
            if (val < minVal_)
                val = minVal_;
            if (val > maxVal_)
                val = maxVal_;
            return val;
        }

    private:
        double mean_;
        double sd_;
        double minVal_;
        double maxVal_;
    };

    class RandStdExponential : public RandGen
    {
    public:
        RandStdExponential (int seed) :
            RandGen (std::string("RandStdExponential"), seed) {}

        double draw() override {return standardExponential();}
    };

    class RandExponential : public RandGen
    {
    public:
        RandExponential (double mean, int seed) :
            RandGen (std::string("RandExponential"), seed),
            mean_(mean)
        {}

        double draw() override {
            return exponential (mean_);
        }

    private:
        double mean_;
    };

}

