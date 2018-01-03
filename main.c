#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>

void ps_lineto(float xfrom, float yfrom, float xto, float yto) {
  printf("newpath %f %f moveto %f %f lineto closepath stroke\n"
	 ,xfrom,yfrom,xto,yto);
}

void gen_grid(int width, int height, int mod) {
  float rightedge=595;/*points*/
  float topedge=842;
  float margin=25;
  float xscale=(rightedge-margin*2)/(width+1.f);
  float yscale=(topedge-margin*4)/(height+2.f);// why 4??
  float scale=xscale < yscale ? xscale : yscale;
  float fontsize = 0.5f; /* in cell units */
  printf("%%!PS-Adobe-3.0\n");
  printf("<< /PageSize [%f %f] >> setpagedevice\n",rightedge,topedge);
  printf("%f %f translate\n",margin*2,margin*3); // why 3??
  printf("%f %f scale\n",scale,scale);
  printf("/Times-Roman findfont %f scalefont setfont\n",fontsize);
  float boldwidth=0.02f;
  /* print the grid */
  for (int x=0; x<=width; x++) {
    float b=x % mod==0 ? boldwidth : 0.f;
    printf("%f %f setlinewidth\n",b,b);
    ps_lineto(x,0, x,height);
  }
  for (int y=0; y<=height; y++) {
    float b=y % mod==0 ? boldwidth : 0.f;
    printf("%f %f setlinewidth\n",b,b);
    ps_lineto(0,y, width, y);
  }
  printf("showpage\n");
}

int main(int argc, char **argv) {
  int width=argc >1 ? atoi(argv[1]) : 10;
  int height=argc >2 ? atoi(argv[2]) : 10;
  int mod=argc >3 ? atoi(argv[3]) : 10;
  gen_grid(width,height,mod);
  return 0;
}
