#ifndef __BREAK_ARR_TEMP_H
#define __BREAK_ARR_TEMP_H

#define MAX_NUM_OF_BREAKS_2	((8)*4)



template <class T, int8 MAX_COUNT>
class BrickArrTemp
{
public:
	int8	m_MaxCount;	
	int8	m_Count;
	T		m_Brick_a[MAX_COUNT];
	int8	m_IterIdx;

//	template <class T, int8 MAX_COUNT>
	BrickArrTemp()
	{
		m_MaxCount = MAX_COUNT;
		m_Count = 0;
	}

	~BrickArrTemp(){}

//	template <class T, int8 MAX_COUNT>
	void Add()
	{
		if (m_Count<m_MaxCount)
		{
			m_Brick_a[m_Count].Init();
			m_Count++;
		}
	}

	void Remove(uint8 a_BrickIdx)
	{
		if ( (a_BrickIdx >= 0) && (a_BrickIdx < m_Count) )
		{
			m_Brick_a[a_BrickIdx] = m_Brick_a[m_Count-1];
			m_Count--;
		}
	}


	void IterBegin()
	{
		m_IterIdx = m_Count;
	}

	T* IterNext()
	{
		if (m_IterIdx>0)
		{
			m_IterIdx--;
			return(&m_Brick_a[m_IterIdx]);
		}
		else
		{
			return(NULL);
		}
	}

	void IterRemove()
	{
		Remove(m_IterIdx);
	}

};

#endif	//	#ifndef __BREAK_H

