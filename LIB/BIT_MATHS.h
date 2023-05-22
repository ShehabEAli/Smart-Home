//This function is to set a specific bit in a variable
#define SET_BIT(num,bit) (num|=(1<<bit))

//This function is to clear a specific bit in a variable
#define CLR_BIT(num,bit) (num&=(~(1<<bit)))

//This function is to toggle a specific bit in a variable
#define TGL_BIT(num,bit) (num^=(1<<bit))

//This function is to get a specific bit in a variable
#define GET_BIT(num,bit) ((num>>bit)&1)
//This function is to write a specific bit in a variable
#define WRT_BIT(num,bit,value) num=(num&~(1<<bit))|(value<<bit)
