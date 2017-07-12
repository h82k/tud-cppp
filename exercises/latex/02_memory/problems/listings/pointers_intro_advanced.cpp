int intVal = 42;
int *pIntVal = &intVal;
*&intVal;
*&pIntVal;
&*pIntVal;
**&pIntVal;
*&*&intVal;
&*&pIntVal;
*&*pIntVal;
