#ifndef _LOCAL_COMM_SORT_VECTOR_H_
#define _LOCAL_COMM_SORT_VECTOR_H_

#include <vector>
#include <string>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

using namespace std;

template<typename T> static inline void sort_vector(vector<T> &v, bool less(const T *a, const T *b))
{
	if(v.size()<1)
		return;

	T* pv[v.size()]; // pointer vector for sorting
	for(size_t i=0; i<v.size(); i++)
	{
		pv[i] = &v[i];
	}

	// do the actual sort based on pointer
	std::sort(pv, pv+v.size(), less);

	size_t iv[v.size()]; // sorted index vector
	for(size_t i=0; i<v.size(); i++)
	{
		iv[i] = pv[i]-&v[0];
	}

	uint32_t n = 0;
	int rev_indexs[v.size()]; // reversed index
	int new_indexs[v.size()]; // positive index

	for(size_t i=0; i<v.size(); i++)
	{
		rev_indexs[i] = new_indexs[i] = i;
	}

	for (size_t j = 0; j < v.size(); ++j)
	{
		uint32_t idx = iv[j]; // store [idx] to [n]
		uint32_t real_idx = rev_indexs[idx];
		if(n!=real_idx)
		{
			if(n>=v.size() || real_idx>=v.size())
			{
				printf("sort_vector: Invalid subfix: size=%lu, n=%u, idx=%u, real_idx=%u\n", v.size(), n, idx, real_idx);
				break;
			}

			// switch new_indexs[n] <-> new_indexs[real_idx]
			uint32_t pos_in_n = new_indexs[n];
			uint32_t pos_in_idx = new_indexs[real_idx];
			new_indexs[n] = pos_in_idx;
			new_indexs[real_idx] = pos_in_n;

			rev_indexs[pos_in_n] = real_idx;
			rev_indexs[pos_in_idx] = n;

			T t = v[n];
			v[n] = v[real_idx];
			v[real_idx] = t;
		}
		n ++;
	}
}

#if 0

struct myst
{
	string a;
	int b;
};

bool cmpst(const myst *a, const myst *b)
{
	if(a->a<b->a)
		return true;
	return false;
}

int main()
{
	vector<myst> v;

	myst a;
	a.a = "alice";
	a.b = 11;
	v.push_back(a);

	a.a = "bob";
	a.b = 2;
	v.push_back(a);

	a.a = "cat";
	a.b = 32;
	v.push_back(a);

	a.a = "bee";
	a.b = 3;
	v.push_back(a);

	sort_vector(v, cmpst);

	for(size_t i=0; i<v.size(); i++)
	{
		printf("%s\n", v[i].a.c_str());
	}
	return 0;
}

#endif
#endif //_LOCAL_COMM_SORT_VECTOR_H_
