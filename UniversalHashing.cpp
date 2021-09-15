#include "UniversalHashing.h"
#include <stdlib.h>
#include <time.h>

#define SizeVectorPrime 200
int primeArray[SizeVectorPrime] = {10007, 10009, 10037, 10039, 10061, 10067, 10069, 10079, 10091, 10093, 10099, 10103, 10111, 10133, 10139, 10141, 10151, 10159, 10163, 10169, 10177, 10181, 10193, 10211, 10223, 10243, 10247, 10253, 10259, 10267, 10271, 10273, 10289, 10301, 10303, 10313, 10321, 10331, 10333, 10337, 10343, 10357, 10369, 10391, 10399, 10427, 10429, 10433, 10453, 10457, 10459, 10463, 10477, 10487, 10499, 10501, 10513, 10529, 10531, 10559, 10567, 10589, 10597, 10601, 10607, 10613, 10627, 10631, 10639, 10651, 10657, 10663, 10667, 10687, 10691, 10709, 10711, 10723, 10729, 10733, 10739, 10753, 10771, 10781, 10789, 10799, 10831, 10837, 10847, 10853, 10859, 10861, 10867, 10883, 10889, 10891, 10903, 10909, 10937, 10939, 10949, 10957, 10973, 10979, 10987, 10993, 11003, 11027, 11047, 11057, 11059, 11069, 11071, 11083, 11087, 11093, 11113, 11117, 11119, 11131, 11149, 11159, 11161, 11171, 11173, 11177, 11197, 11213, 11239, 11243, 11251, 11257, 11261, 11273, 11279, 11287, 11299, 11311, 11317, 11321, 11329, 11351, 11353, 11369, 11383, 11393, 11399, 11411, 11423, 11437, 11443, 11447, 11467, 11471, 11483, 11489, 11491, 11497, 11503, 11519, 11527, 11549, 11551, 11579, 11587, 11593, 11597, 11617, 11621, 11633, 11657, 11677, 11681, 11689, 11699, 11701, 11717, 11719, 11731, 11743, 11777, 11779, 11783, 11789, 11801, 11807, 11813, 11821, 11827, 11831, 11833, 11839, 11863, 11867, 11887, 11897, 11903, 11909, 11923, 11927};
bool isRand = false;

struct UndavUniversalHashing::UniversalHashing{
	int a;
	int b;
};

int GetRandomPosition(int maxPosition);
int SetRandomValue(int exception = 0);

UndavUniversalHashing::UniversalHashing* UndavUniversalHashing::Create()
{
	UniversalHashing* newUniversalHashing = new UniversalHashing;
	if(!isRand){
		srand(time(NULL));
		isRand = true;
	}
	newUniversalHashing->a = SetRandomValue();
	newUniversalHashing->b = SetRandomValue(newUniversalHashing->a);
	return newUniversalHashing;
}

int UndavUniversalHashing::Hash(const UniversalHashing* universalHashing, const char* key, int maximumHashCode)
{
	if(maximumHashCode <= 1) return 0;
	int hashCode;
	int a = universalHashing->a;
	int b = universalHashing->b;
	for (hashCode = 0; *key != '\0'; ++key, a = a * b % (maximumHashCode - 1))
	{
		hashCode = (a * hashCode + *key) % maximumHashCode;
	}
	return hashCode;
}

void UndavUniversalHashing::Destroy(UniversalHashing* universalHashing)
{
	delete[] universalHashing;
}

int GetRandomPosition(int maxPosition)
{
	return rand() % maxPosition;
}

int SetRandomValue(int exception){
	int number = primeArray[GetRandomPosition(SizeVectorPrime)];
	while(number == exception){
		number = primeArray[GetRandomPosition(SizeVectorPrime)];
	}
	return number;
}
