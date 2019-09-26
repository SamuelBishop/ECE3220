//
// SYNOPSYS
//      ./generate [OPTION ...]
//
// OPTIONS
//  -f file_number
//      An integer between 0 and 99 inclusive that specifies the name of
//      the file to be generated. For example, if file_number is 3, the
//      generated file name is `read_data_03.txt'. If this option is not
//      specified, file_number defaults to zero which generates a file
//      named `read_data_00.txt'.
//
//  -L data_set_size
//      An integer that specifies the number of data values to be stored in
//      the generated file.
//
//  -M max_data_value
//      An integer that specifies the maximum data value to be stored in
//      the generated file.
//
//  -o sequence_type
//      Any one of:
//          0 - Random numbers between 0 and cloMaxDataValue (this is the
//              default)
//          1 - periodic increasing values
//          2 - alternating values between 0 and cloMaxDataValue (only
//              those two)
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char *argv[])
{
	int i = 1;
    int cloSequenceType = 0;
    int cloDataSetSize = 10;
    int cloMaxDataValue = 10;
    int cloFileNumber = 1;
	
	// Handle input arguments
	while (i < argc) {
        if((argv[i][0] == '-') && (argv[i][1] == 'f')) {
            cloFileNumber = atoi(argv[i+1]);
            i = i + 2; }
        else if((argv[i][0] == '-') && (argv[i][1] == 'L')) {
            cloDataSetSize = atoi(argv[i+1]);
            i = i + 2; }
        else if((argv[i][0] == '-') && (argv[i][1] == 'M')) {
            cloMaxDataValue = atoi(argv[i+1]);
            i = i + 2; }
        else if((argv[i][0] == '-') && (argv[i][1] == 'o')) {
            cloSequenceType = atoi(argv[i+1]);
			i = i + 2; }
		else
			i++;
	}
	
	FILE *fp_w;
	char fullname[50]; // for file names
	int value;
	
	srand(time(NULL)); // randomize seed

	sprintf(fullname, "raw_data_%02d.txt", cloFileNumber);
	fp_w = fopen(fullname,"w");  // open for writing
	
	if(fp_w == NULL)
		perror("Error opening file");
	else {
		fprintf(fp_w, "%d %d\n", cloDataSetSize, cloMaxDataValue);
		for(i = 0; i < cloDataSetSize; i++)
		{
			switch(cloSequenceType) {
				case 1: // periodic increasing
					value = i%(cloMaxDataValue+1);
					break;
				case 2: // alternating between 0 and cloMaxDataValue (only those two)
					value = (i%2)*cloMaxDataValue;
					break;
				default: // random number between 0 and cloMaxDataValue
					value = rand()%(cloMaxDataValue+1);
					break;
			}
			fprintf(fp_w, "%d\n", value);
		}
	}
	fclose(fp_w);
	
	printf("Done creating file %s.\n\n", fullname);

	return 0;
}
