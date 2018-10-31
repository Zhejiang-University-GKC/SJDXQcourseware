////////////////////////////////////////////////////////////////////////////////
#pragma once
////////////////////////////////////////////////////////////////////////////////

// ImageColorHelper

class ImageColorHelper
{
public:
	// Rgb2Hsv
	static void Rgb2Hsv(float R, float G, float B, float& H, float& S, float&V)
	{  
		// r,g,b values are from 0 to 1
		// h = [0,360], s = [0,1], v = [0,1]
		// if s == 0, then h = -1 (undefined)
		float min, max, delta, tmp;

		tmp = R>G?G:R;
		min = tmp>B?B:tmp;
		tmp = R>G?R:G;
		max = tmp>B?tmp:B;
		V = max; // v
		delta = max - min;

		if( max != 0 ) {
			S = delta / max; // s
		} else {
			// r = g = b = 0 // s = 0, v is undefined
			S = 0;
			H = 0;
			return;
		}

		if (delta == 0) {
			H = 0;
			return;
        } else if(R == max) {
			if (G >= B) {
				H = (G - B) / delta;     // between yellow & magenta
			} else {
				H = (G - B) / delta + 6;
			}
		} else if( G == max ) {
			H = 2 + ( B - R ) / delta; // between cyan & yellow
		} else if (B == max)  {
			H = 4 + ( R - G ) / delta; // between magenta & cyan
		}

		H *= 60; // degrees
	}
	// Hsv2Rgb
	static void Hsv2Rgb(float H, float S, float V, float& R, float& G, float&B)
	{
		// r,g,b values are from 0 to 1
		// h = [0,360], s = [0,1], v = [0,1]
		int i;
		float f, p, q, t;

		if( S == 0 ) {
			// achromatic (grey)
			R = G = B = V;
			return;
		}

		H /= 60; // sector 0 to 5
		i = (int)floor( H );
		f = H - i; // factorial part of h
		p = V * ( 1 - S );
		q = V * ( 1 - S * f );
		t = V * ( 1 - S * ( 1 - f ) );

		switch( i ) 
		{
		case 0: 
			R = V;
			G = t;
			B = p;
			break;
		case 1:
			R = q;
			G = V;
			B = p;
			break;
		case 2:
			R = p;
			G = V;
			B = t;
			break;
		case 3:
			R = p;
			G = q;
			B = V;
			break;
		case 4:
			R = t;
			G = p;
			B = V;
			break;
		default: // case 5:
			R = V;
			G = p;
			B = q;
			break;
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
