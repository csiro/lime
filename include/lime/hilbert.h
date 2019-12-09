#pragma once

#include <map>
#include <vector>
#include <memory>

namespace lime
{

    /** A class to convert a point into a point on the hilbert curve
     */
    class Hilbert
    {
    public:
        
        /* Set up a Hilbert curve.width and height define the bounding box
         * of the area we are working in
     */
        Hilbert (double width, double height) :
            width_(width),
            height_(height),
            maxIndex_(0),
            iSize_(0),
            nthbits_(0)
        {
            setBits (14);
        }
        
        Hilbert (int nBits, double width, double height) :
            width_(width),
            height_(height),
            maxIndex_(0),
            iSize_(0),
            nthbits_(0)
        {
            setBits(nBits);
        }

        /** set the number of bits and associated fields */
        void setBits (int nBits)
        {
            if (nBits % 2 == 1)
                nBits++;
            if (nBits >= 15)
                nBits = 14;
            nBits_ = nBits;
            nthbits_ = (((1 << 2 * nBits) - 1) / 3) >> 1;
            iSize_ = 1 << (nBits / 2);
            maxIndex_ = 1 << nBits;
        }
        
        void posToCoord (double pos, double& x, double& y)
        {
            long index = (long)(pos * maxIndex_);
            int coord[2];
            
            indexToCoord (index % maxIndex_, coord);
            x = (coord[0] + 0.5) * width_/iSize_;
            y = (coord[1] + 0.5) * height_/iSize_;
        }

        /* Return the pos in [0,1] closest to a given coordinate */
        double coordToPos (double x, double y)
        {
            int coord[2];
            coord[0] = (int)((iSize_ * x / width_) - 0.5);
            coord[1] = (int)((iSize_ * y / height_) - 0.5);
            long index = coordToIndex (coord);
            return (double)index / maxIndex_;
        }
    
        /*****************************************************************
         * (was) hilbert_i2c
         * Convert an index in the range [0, 1 << nBits] to a coord
         * Coord x and y are in the range [0, 1 << nBits/2];
         */
        void indexToCoord (long index, int coord[])
        {
            int b,d;
            int rotation = 0; /* or (nBits * (2-1)) % 2; */
            long reflection = 0;
            
            coord[0] = coord[1] = 0;

            index ^= index >> 1;
            index ^= nthbits_;
  
            for (b = nBits_; b-- > 0;) {
                long bits = (index >> 2*b) & ND_ONES;
                reflection ^= ((bits >> rotation) | (bits << (2-rotation))) & 3;
            
                coord[0] |= (reflection & 1) << b;
                coord[1] |= ((reflection >> 1) & 1) << b;
                reflection ^= ONE << rotation;

                // adjust rotation
                bits &= -bits & 1;
                while (bits != 0) {
                    bits >>= 1;
                    ++rotation;
                }
                if (++rotation >= 2)
                    rotation -= 2;
            }
        }


        /*****************************************************************
         * (was) hilbert_c2i
         * Convert an index in the range [0, 1 << nBits] to a coord
         * Coord x and y are in the range [0, 1 << nBits/2];
         * 
         */
        long coordToIndex(int coord[])
        {
            int b, d;
            int rotation = 0; /* or (nBits * (2-1)) % 2; */
            long reflection = 0;
            long index = 0;

            for (b = nBits_; b-- > 0;) {
                long bits = reflection;
                reflection = 0;
                for ( d = 0; d < 2; d++ )
                    reflection |= ((coord[d] >> b) & 1 ) << d;
                bits ^= reflection;
                
                bits = ((bits >> (rotation)) | ((bits) << (2-rotation))) & 3;
            
                index |= bits << 2*b;
                reflection ^= ONE << rotation;

                // adjust rotation
                bits &= -bits & 1;
                while (bits != 0) {
                    bits >>= 1;
                    ++rotation;
                }
                if (++rotation >= 2)
                    rotation -= 2;
            }
            index ^= nthbits_;
            /*
              for (d = 1; index >> d; d *= 2)
              index ^= index >> d;
            */ 
            for (d = 1; true; d *= 2) {
                long t;
                if (d <= 32) {
                    t = index >> d;
                    if (t == 0)
                        break;
                }
                else {
                    t = index >> 32;
                    t = t >> (d - 32);
                    if (t == 0)
                        break;
                }
                index ^= t;
            }
            return index;
        }
        
    private:
        enum {ONE = 1, ND_ONES = 3};
        
        double width_;
        double height_;
    
        int nBits_;
        // maxIndex - maximum Index
        int maxIndex_;
        // iSize is the length of the side
        int iSize_;

        long nthbits_;
    };

    using HilbertPtr = std::shared_ptr<Hilbert>;
}

