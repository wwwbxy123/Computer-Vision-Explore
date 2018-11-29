/*******************************************************************/
/* vcom return the left lower corner of a byte image            */
/*******************************************************************/
#include "VisXV4.h" 
#include "Vutil.h"
VXparam_t par[] =
{ /* prefix, value,*/
{ "if=", 0, " input file vcorner: copy lower left corner"}, 
{ "of=", 0, " output file "},
{ 0, 0, 0} /* list termination */
};

#define IVAL par[0].val
#define OVAL par[1].val

int main(argc, argv) 
int argc;
char *argv[];
{
/* VisionX structure include file    */
/* VisionX utility header files      */
/* command line structure            */
/* description                         */
	Vfstruct (im); 
	Vfstruct (tm); 
	int y,x; 
	int s;
	float bbx[6];
	int m00=0;
	int m01=0;
	int m10=0;
	int xx=0;
	int yy=0;	
	VXparse(&argc, &argv, par); /* parse the command line */	
	/* create VX image for result */
	s = 400; /* set size of result image */ 
	bbx[0] = bbx[2] = bbx[4] = bbx[5] = 0.0; bbx[1] = bbx[3] = s;
	Vfnewim(&tm, VX_PBYTE, bbx, 1);
	while ( Vfread(&im, IVAL) ) { /* read image file */ 
		if ( im.type != VX_PBYTE ) { /* check image format */ 
			fprintf(stderr, "vcorner: no byte image data in input file\n");
			exit(-1); 
		}

     /* check that the input image is large enough */
		if ( (im.xhi - im.xlo ) < (tm.xhi - tm.xlo) ||(im.yhi - im.ylo ) < (tm.yhi - tm.ylo) ) { 
    			fprintf(stderr, "vcorner: input image too small\n"); 
			exit(-1);
		}



		for(y = im.ylo; y <= im.yhi; y++){
		    for(x = im.xlo; x <= im.xhi; x++){
			if( im.u[y][x] == 0){
			    m00++;
			}
		    }
		}

		for(y = im.ylo; y <= im.yhi; y++){
		    for(x = im.xlo; x <= im.xhi; x++){
			if( im.u[y][x] == 0){
			    m01 = x + m01;
			    m10 = y + m10;
			}
		    }
		}

		xx = m01 / m00;
		yy = m10 / m00;

		printf("xx = %d \n", xx);
		printf("yy = %d \n", yy);
		im.xlo = xx - 200;
		im.ylo = yy - 200;

		for(y = tm.ylo; y <= tm.yhi; y++){
		    for(x = tm.xlo; x <= tm.xhi; x++){
			tm.u[y][x] = im.u[y + im.ylo][x + im.xlo];
		    }
		}


		Vfwrite(&tm, OVAL);
	}	
		exit(0); 
}
/* write image file                */
