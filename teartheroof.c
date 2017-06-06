#include <stdio.h>
#include <stdlib.h>

struct PPMPixel
{
    char red;
    char blue;
    char green;
};

struct PPMImage
{
     unsigned x, y;
     struct PPMPixel *data;
};

#define CREATOR "RPFELGUEIRAS"
#define RGB_COMPONENT_COLOR (255)

static struct PPMImage *readPPM()
{
     char buff[16];
     struct PPMImage *img;

     FILE *fp;

     int c;
     int rgb_comp_color;

     //open PPM file for reading
     fp = fopen("ukraine.ppm", "rb");
     if (!fp)
     {
         perror( "fopen for ukraine.ppm failed" );
         // fprintf(stderr, "Unable to open file '%s'\n", filename);
          exit(1);
     }

     // implied els,e fopen successful

     //read image format // get first 15 bytes of image file
     if (!fgets(buff, sizeof(buff), fp))
     {
          perror("ukraine.ppm");
          exit(1);
     }

     // implied else, fgets successful

    //check the image format
    if (buff[0] != 'P' || buff[1] != '6') {
         fprintf(stderr, "Invalid image format (must be 'P6')\n");
         exit(1);
    }

    // implied else, image file file has correct format indicators

    //alloc memory for image
    img = malloc(sizeof(struct PPMImage));
    if (!img)
    {
        perror( "malloc for PPMImage failed" );
        //fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    // implied else, malloc successful

    //check for comments
    c = getc(fp);
    while (c == '#')
    {
        while( (c = getc(fp)) != '\n') ;
    }

    //read image size information
    if (fscanf(fp, "%u %u", &img->x, &img->y) != 2)
    {
        perror( "fscanf for ukraine.ppm image size parameters failed" );
         exit(1);
    }

    // implied else, fscanf successful

    //read rgb component
    if (fscanf(fp, "%d", &rgb_comp_color) != 1)
    {
        perror( "fscanf for rgb_comp_color in ukraine.ppm failed" );
         //fprintf(stderr, "Invalid rgb component (error loading '%s')\n",      filename);
         exit(1);
    }

    // implied else, fscanf successful

    //check rgb component depth
    if (rgb_comp_color!= RGB_COMPONENT_COLOR)
    {
         fprintf(stderr, "'ukraine.ppm' does not have 8-bits components\n");
         exit(1);
    }

    // implied else, rgb component depth correct

    // consume rest of line
    while (fgetc(fp) != '\n') ;

    //memory allocation for pixel data
    img->data = malloc(img->x * img->y * sizeof( struct PPMPixel));

    if ( !img->data ) //< corrected element being checked
    {
        perror( "malloc for pixel data failed" );
        //fprintf(stderr, "Unable to allocate memory\n");
         exit(1);
    }

    // implied else, malloc successful

    //read pixel data from file
    if (fread(img->data, 3 * img->x, img->y, fp) != img->y)
    {
        perror( "fread for pixel data failed" );
        // fprintf(stderr, "Error loading image '%s'\n", filename);
         exit(1);
    }

    // implied else, fread successful

    fclose(fp);
    return img;
} // end function: readPPM


void writePPM(struct PPMImage *img)
{
    FILE *fp;
    //open file for output
    fp = fopen("ukraine.ppm", "wb");
    if (!fp)
    {
        perror( "fopen for ukraine.ppm for write failed" );
        // fprintf(stderr, "Unable to open file '%s'\n",filename);
         exit(1);
    }

    // implied else, fopen successful

    //write the header file
    //image format
    fprintf(fp, "P6\n");

    //comments
    fprintf(fp, "# Created by %s\n",CREATOR);

    //image size
    fprintf(fp, "%d %d\n",img->x,img->y);

    // rgb component depth
    fprintf(fp, "%d\n",RGB_COMPONENT_COLOR);

    // pixel data
    fwrite(img->data, 3 * img->x, img->y, fp);
    fclose(fp);
} // end function: writePPM


void changeColorPPM(struct PPMImage *img)
{
    unsigned i;
    if(img)
    {

         for(i=0;i<img->x*img->y;i++)
         {
              img->data[i].red=RGB_COMPONENT_COLOR-img->data[i].red;
              img->data[i].green=RGB_COMPONENT_COLOR-img->data[i].green;
              img->data[i].blue=RGB_COMPONENT_COLOR-img->data[i].blue;
         }
    }
} // end function: changeColorPPM


int main()
{
    struct PPMImage *image;
    image = readPPM();
    //changeColorPPM(image);
    writePPM(image);
    printf("Press any key...");
    getchar();

    return(0);
}
