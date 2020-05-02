// Problem_1_Floating_Point.cpp : Defines the entry point for the application.
//

#include <stdio.h>

union float_bits {
	float f;
	unsigned int bits;
};

typedef struct float_list {
	union float_bits* floatNumbers;
	unsigned int nFloats;
} float_list;

// read floating point numbers from file
void readFloats(float_list* floatList, const char const* fileName) {
	FILE* inputData = fopen(fileName, "r");

	const int nFloats;
	fscanf(inputData, "%d", &nFloats); 
	floatList->nFloats = nFloats; 

	union float_bits* floatNumbers = floatList->floatNumbers;

	for (int i = 0; i < floatList->nFloats; i++) {
		union float_bits floatNumber;
		fscanf(inputData, "%f", &(floatNumber.f));
		floatNumbers[i] = floatNumber;
		/*char floatString[100];
		fscanf(inputData, "%s", floatString);
		printf(floatString);
		printf("\n");*/
	}
	floatList->floatNumbers = floatNumbers;

	fclose(inputData);
}

// write binary representation of floating point numbers to output file
void writeFloats(float_list* floatList, const char const* fileName) {
	const short bias = 127;
	FILE* outputFile = fopen(fileName, "w");	

	union float_bits* floatNumbers = floatList->floatNumbers;
	for (int i = 0; i < floatList->nFloats; i++) {
		unsigned int floatBits = floatNumbers[i].bits;

		unsigned short sign = 0;
		char exponent = 0; // 1 byte int
		unsigned int mantisse = 0;

		mantisse = floatBits & 0x007FFFFF; // take the first 23 bits from floatbits
		floatBits = floatBits >> 23; // shift to the right by 23
		exponent = floatBits; // take the first 8 bits
		floatBits = floatBits >> 8; // shift to the right by 8
		sign = floatBits;

		// if number is negative
		if (sign) {
			fprintf(outputFile, "-"); 
		}

		if (exponent != 0) {
			// print mantisse
			fprintf(outputFile, "1.");
			short mantissebit = 0;
			for (int j = 0; j < 23; j++) {
				mantissebit = (mantisse >> (22 - j)) & 0x0001;
				fprintf(outputFile, "%u", mantissebit);
			}

			// print exponent
			fprintf(outputFile, " %c %d%c%d", '*', 2, '^', exponent - bias);
			fprintf(outputFile, "\n");
		}
		else {
			// print mantisse
			fprintf(outputFile, "0.");
			short mantissebit = 0;
			for (int j = 0; j < 23; j++) {
				mantissebit = (mantisse >> (22 - j)) & 0x0001;
				fprintf(outputFile, "%u", mantissebit);
			}

			// print exponent
			fprintf(outputFile, " %c %d%c%d", '*', 2, '^', -126);
			fprintf(outputFile, "\n");
		}		

		printf("Exponent: ");
		printf("%d", exponent);
		printf("\n");

		/*printf("Sign: ");
		printf("%X", sign);
		printf("\n");	
		printf("Mantisse: ");
		printf("%X", mantisse);
		printf("\n");*/
		/*fprintf(outputFile, "%f", floatNumbers[i].f);
		fprintf(outputFile, "\n");*/
	}

	fclose(outputFile);
}

// write binary representation of floating point numbers to output file
int main() {
	const char* inputFile = "floating.7.in";
	const char* outputFile = "float.out";

	float_list floatList;
	union float_bits floatNumbers[1000]; // max 1000 number of floats
	floatList.floatNumbers = floatNumbers;

	readFloats(&floatList, inputFile);
	writeFloats(&floatList, outputFile);
}
