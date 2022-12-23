#include <iostream>
#include <vector>
#include <random>

using namespace std;


//======================================================================================================
// <문제1>
//
// 링크드 리스트를 구현하라.
// 데이터 타입은 템플릿을 사용한다.
//======================================================================================================

template<typename T>
class Node
{
public:
	Node(T InValue) 
		: m_Value(InValue)
		, m_Next(nullptr)
	{}

	T m_Value;
	Node<T>* m_Next;
};

template<typename T>
class LinkedList
{
public:
	LinkedList() 
		: m_Size(0) 
	{}

	void Add(T InValue)
	{
		if (m_Head == nullptr)
		{
			//	헤드가 없으면 헤드에 저장
			m_Head = new Node<T>(InValue);
		}
		else
		{
			Node<T>* PrevNode = nullptr;
			PrevNode = m_Head;

			while (PrevNode->Next != nullptr)
			{
				PrevNode = PrevNode->Next;
			}

			PrevNode->Next = new Node<T>(InValue);
		}

		++m_Size;
	}

	void Add(Node<T>* InPrevNode, T InValue)
	{
		if (InPrevNode == nullptr)
		{
			//	error!
			return;
		}

		Node<T>* NewNode = new Node<T>(InValue);
		NewNode->Next = InPrevNode->Next;
		InPrevNode->Next = NewNode;

		++m_Size;		
	}

	void Remove(int InRemoveValue)
	{
		Node<T>* RemoveNode = Get(InRemoveValue);
		if (RemoveNode == nullptr)
		{
			cout << "찾는값이 없음" << endl;
			return;
		}

		Node<T>* PrevNode = m_Head;

		while (PrevNode != nullptr && PrevNode->Next != RemoveNode)
		{
			PrevNode = PrevNode->Next;
		}
		PrevNode->Next = RemoveNode->Next;

		if (RemoveNode == m_Head)
		{
			//	헤드를 지울거라면 헤드 갱신
			m_Head = m_Head->Next;
		}

		delete RemoveNode;
		--m_Size;
	}

	void Remove(Node<T>* InRemoveNode)
	{
		Node<T>* PrevNode = m_Head;
		while (PrevNode != nullptr && PrevNode->Next != InRemoveNode)
		{
			PrevNode = PrevNode->Next;
		}
		PrevNode->Next = InRemoveNode->Next;

		if (InRemoveNode == m_Head)
		{
			//	헤드를 지울거라면 헤드 갱신
			m_Head = m_Head->Next;
		}

		delete InRemoveNode;
		--m_Size;
	}

	Node<T>* Get(int InValue)
	{
		Node<T>* FindNode = m_Head;
		while (FindNode != nullptr && FindNode->m_Value != InValue)
		{
			FindNode = FindNode->Next;
		}

		return FindNode;
	}

	int GetSize()
	{
		return m_Size;
	}

	void Print()
	{
		Node<T>* CurNode = m_Head;
		while (CurNode != nullptr)
		{
			cout << CurNode->m_Value << endl;
			CurNode = CurNode->Next;
		}
	}

private:
	int m_Size = 0;
	Node<T>* m_Head;
};




//======================================================================================================
// <문제2>
//
// 몬스터가 각각의 스킬을 사용할 확률이 다음과 같다.
// Skill* pSkill1(15), pSkill2(25), pSkill3(10)
// 각각의 확률 값은 상대적인 값이므로 실제 확률은 30%(15/50), 50%(25/50), 20%(10/50)가 된다.

// pSkill1, pSkill2, pSkill3와 상대 확률(15, 25, 10)의 입력값으로 랜덤하게 하나의 스킬(pSkill*)을 
// 선택하는 함수를 작성하라. 

// 입력값(pSkill1, 15)은 꼭 3개가 아니라 1개일수도 있고 수십개 일수도 있다.
// 또한 입력값의 타입이 특정 타입의 클래스(Skill)가 아니더라도 결과를 얻어낼 수 있어야 한다. 템플릿 사용 필요.

// 다음과 같은 형태의 함수 2개가 필요하다. 
// void AddRandom(int Prob, const T& Data);
// bool GetRandom(T& Data) const;
//======================================================================================================

template<typename T>
class SkillRandom
{
public:
	SkillRandom() 
		: m_MaxProb(0)
	{}

	void AddRandom(int InProb, const T& InData)
	{
		if (InProb <= 0)
		{
			cout << "확률값이 이상함" << endl;
			return;
		}

		m_MaxProb += InProb;
		
		m_SkillList.push_back(make_pair(InData, InProb));
	}

	bool GetRandom(T& Data) const
	{
		if (m_SkillList.size() <= 0)
		{
			cout << "skill list가 비어있음!" << endl;
			return false;
		}

		if (m_MaxProb <= 0)
		{
			cout << "확률값이 없음!" << endl;
			return false;
		}

		//	랜덤 뽑기
		random_device RandomDevice;
		mt19937 Mt(RandomDevice());
		uniform_int_distribution<int> Rand(1, m_MaxProb);
		int RandIndex = Rand(Mt);

		if (RandIndex == m_MaxProb)
		{
			//	랜덤값이 끝값이라면
			//	마지막값 바로 리턴
			Data = m_SkillList[m_SkillList.size() - 1].first;
			return true;
		}

		bool ReturnValue = false;
		for (int i = 0; i < m_SkillList.size(); ++i)
		{
			RandIndex -= m_SkillList[i].second;
			if (RandIndex <= 0)
			{
				Data = m_SkillList[i].first;
				ReturnValue = true;
				break;
			}
		}
		
		return ReturnValue;
	}

private:
	vector<pair<T, int>> m_SkillList;
	int m_MaxProb;
};



int main()
{
	
	return 0;
}
