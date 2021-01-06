#pragma once
#include<iostream>
#include<string>
#include<vector>
#include <cmath>
using namespace std;

template<typename T>
class Node {//����ģ�嶨��һ�����
	template<typename T>//Ҫ��Stack����Ϊ��Ԫ
	friend class Stack;//Ӧ����ǰ����������������дfriend class Stack<T>
	T m_data;//������
	Node* m_next = nullptr;//ָ����һ������ָ�루ָ��node���͵�ָ�룩�����������ָ�����������͵�ָ�� �����ã�
public:
	Node(const T& val) :m_data(val) {}//���캯�������������ʼ��
	const T& data()const { return m_data; }//const �汾���������ã���T&data�޶����Ժ��������޶���
	T& data() { return m_data; }//��const�汾��д������
	Node* next() { return m_next; }//����ָ����һ��ָ��
};


template<typename T>
class Stack {
	Node<T>* m_top = nullptr;//ͷָ��
public:
	Stack() = default;//Ĭ�Ϲ��캯��
	Stack(const Stack&) = delete;//��ֹ����
	Stack& operator =(const Stack&) = delete;//��ֹ��ֵ
	~Stack();
	void clear();//���ջ
	void push(const T& val);//��ջ
	void pop();//��ջ
	bool empty()const { return m_top == nullptr; }//�Ƿ�Ϊ��
	const T& top() { return m_top->m_data; }//ȡջ��Ԫ�أ���ջ��Ԫ��ֻ�ܽ��ж�������
};

template<typename T>
void Stack<T>::push(const T& val) {//��ջ
	Node<T>* node = new Node<T>(val);//����һ���½�㣨nodeָ���´����Ķ�̬�ڴ棩
	node->m_next = m_top;//�����nodeѹջ,��nodeָ��Ľ���m_nextָ��m_top
	m_top = node;//�޸�ջ��ָ�룬��m_topָ��node���
}

template<typename T>
void Stack<T>::pop() {//��ջ
	Node<T>* p = m_top;//��ջ��Ԫ�ص�ַ��ŵ�ָ��p��
	m_top = m_top->m_next;//�޸�ջ��ָ�룬��m_topָ��m_topָ�����һ�����
	delete p;//�ͷ��ͷ�ָ��pָ����ڴ棬����������������������ڴ�й¶����ջ���Ǹ��ڴ�δ����
}

template<typename T>
void Stack<T>::clear() {//���ջ
	Node<T>* p = nullptr;//����ָ�룬����Э����ջ,ͬ��
	while (m_top != nullptr) {
		p = m_top;
		m_top = m_top->m_next;
		delete p;
	}
}

template<typename T>
Stack<T>::~Stack() {//��������
	clear();
}



class Calculator {//��������
private:
	Stack<double>m_num;//������ջ
	Stack<char>m_opr;//�����ջ
	int precedence(const char& s)const;//��ȡ��������ȼ������ɶ�������ͺ��������д������
	double readNum(string::const_iterator& it);//��ȡ������
	void calculator();//ȡ��������Ͳ��������м���
	bool isNum(string::const_iterator& c)const {//�����������ж��Ƿ�Ϊ���֣����ɶԺ��������д������
		return *c >= '0' && *c <= '9' || *c == '.';//����Ϊ0��9��������.������С��
	}
public:
	Calculator() { m_opr.push('#'); }//�����ջ��ʼ��,�����ȼ���͵�#����
	double doIt(const string& exp);//���ʽ��ֵ�����ɶԱ��ʽ����д������
};

int Calculator::precedence(const char& s)const {//��ȡ��������ȼ������ɶ�������ͺ��������д������
	switch (s) {
	case'=':return 0;
	case'#':return 1;
	case'+':case'-':return 2;
	case'*':case'/':case'%':return 3;
	case'^':return 4;
	case's':case'c':case't':case'r':return -1;//�ں�������ж��Ƿ�Ϊsin cos tan sqrt
	case'S':case'C':case'T':case'R':return 5;
	case'(':case')':return 6;
		
	}
}

double Calculator::readNum(string::const_iterator& it) {//��ȡ������
	string t;
	while (isNum(it) || (*it == 'p'))//�ж��Ƿ�Ϊ���֣�����ǣ�������ָ���һ����ɨ�裬ֱ�����������
	if (*it == 'p') {//�ж��ǲ���pi
		++it;
		if (*it == 'i') {
			++it;
			return (atan(1.0) * 4);
		}
		else {
			//������ǣ�����
			cout << "���ʽ����������-1������" << endl;
			return -1;
		}
	}
	else//�������pi��������ȡ��
		t += *it++;
	return stod(t);//�������ַ���ת��Ϊdouble����                                                         
}

void Calculator::calculator() {//ȡ��������Ͳ��������м���
	double b = m_num.top();//ȡ���Ҳ�����
	double a=0;//����a����ȡ�������
	m_num.pop();//�Ҳ�������ջ
	if ((m_opr.top() != 'S')&& (m_opr.top() != 'C') && (m_opr.top() != 'T') && (m_opr.top() != 'R')) {//����sin,cos,tan,sqrt��Ŀ�������ȡ����������
		a = m_num.top();//ȡ���������
	    m_num.pop();//���������ջ
	}
	if (m_opr.top() == '+')//��Ϊ�ӣ���(a + b)ѹջ
		m_num.push(a + b);
	else if (m_opr.top() == '-')//��Ϊ������(a - b)ѹջ
		m_num.push(a - b);
	else if (m_opr.top() == '*')//��Ϊ�ˣ���(a * b)ѹջ
		m_num.push(a * b);
	else if (m_opr.top() == '/')//��Ϊ������(a / b)ѹջ
		m_num.push(a / b);
	else if (m_opr.top() == '%')//��Ϊ���࣬��(a % b)ѹջ
		m_num.push(fmod(a, b));
	else if (m_opr.top() == '^')//��Ϊ���ݣ���a^bѹջ
		m_num.push(pow(a,b));
	else if (m_opr.top() == 'S') {//��Ϊsin����sin(b)ѹջ
		m_num.push(sin(b));
	}
	else if (m_opr.top() == 'C') {//��Ϊcos����cos(b)ѹջ
		m_num.push(cos(b));
	}
	else if (m_opr.top() == 'T') {//��Ϊtan����tan(b)ѹջ
		m_num.push(tan(b));
	}
	else if (m_opr.top() == 'R') {//��Ϊsqrt����sqrt(b)ѹջ
		m_num.push(sqrt(b));
	}
	m_opr.pop();//��ǰ����������������ջ
}

double  Calculator::doIt(const string& exp) {//���ʽ��ֵ�����ɶԱ��ʽ����д������
	m_num.clear();//��֤ͬһ�������ٴε���doItʱ������ջΪ��
	for (auto it = exp.begin(); it != exp.end();) {//��ʼ����������itָ����ʽ�ĵ�һ�����жϾ�Ϊ��itû��ָ����ʽ���һ��
		if (isNum(it)||(*it == 'p')) {//������������ʱ,������pʱ��������pi
			m_num.push(readNum(it));//��ȡ��������������ջ
		}
		else {
			while ((precedence(*it) <= precedence(m_opr.top())) || (*it == ')')|| (precedence(*it)==-1)) {//���������ʱ���ж�����ָ�����������ȼ��������ջ�������ȼ�����С�ڵ��������ѭ��(���ȼ��͵��Ƚ�ȥ����ѹ��)
																				 //���ߵ�itָ�򡮣���ʱ����Ҫ��ʼ���������ڶ���
				                                                                 //���ߵ����ȼ�Ϊ-1ʱ����Ҫ�����ж��Ƿ�Ϊsin,cos tan,sqrt
				if ((m_opr.top() == '(') && (*it != ')')&& (*it != 's') && (*it != 'c') && (*it != 't')) {//�����ʱջ����'('����itֵ�Ĳ��ǡ����������������ȼ���������������ջ��(ͨ��ѭ�������Ǹ�if�����ջ)
					break;                                                                                //ͬʱ����(sin)������
				}
				if ((m_opr.top() == '(') && (*it == ')')) {//�����ʱջ����'('����itֵ���ǡ��������������ڴ�����ϣ�
					m_opr.pop();//������������ȥ
					break;
				}

				if (*it == 's') {//�ж��Ƿ�Ϊsin
					++it;
					if (*it == 'i') {
						++it;
						if (*it == 'n') {//����sin����Sѹջ������sin,��break����
							m_opr.push('S');
							break;
						}
						else {//������ǣ�����
							cout << "���ʽ����������-1������" << endl;
							return -1;
						}
					}
					else {//������ǣ�it�˻�ȥ,�п�����sqrt
						--it;
					}
				}

				if (*it == 'c') {//�ж��Ƿ�Ϊcos
					++it;
					if (*it == 'o') {
						++it;
						if (*it == 's') {//����cos����Cѹջ������cos,��break����
							m_opr.push('C');
							break;
						}
						else {//������ǣ�����
							cout << "���ʽ����������-1������" << endl;
							return -1;
						}
					}
					else {//������ǣ�����
						cout << "���ʽ����������-1������" << endl;
						return -1;
					}
				}

				if (*it == 't') {//�ж��Ƿ�Ϊtan
					++it;
					if (*it == 'a') {
						++it;
						if (*it == 'n') {//����tan����Tѹջ������tan,��break����
							m_opr.push('T');
							break;
						}
						else {//������ǣ�����
							cout << "���ʽ����������-1������" << endl;
							return -1;
						}
					}
					else {//������ǣ�����
						cout << "���ʽ����������-1������" << endl;
						return -1;
					}
				}

				if (*it == 's') {//�ж��Ƿ�Ϊsqrt
					++it;
					if (*it == 'q') {
						++it;
						if (*it == 'r') {
								++it;
							if (*it == 't') {//����sqrt����Rѹջ������sqrt,��break����
								m_opr.push('R');
							    break;
							}
							else {//������ǣ�����
								cout << "���ʽ����������-1������" << endl;
								return -1;
							}
						}
						else {//������ǣ�����
							cout << "���ʽ����������-1������" << endl;
							return -1;
						}
					}
					else {//������ǣ�����(ǰ���ж��˲���sin�������ﻹ����sqrt�Ļ����ǵ���s������)
						cout << "���ʽ����������-1������" << endl;
						return -1;
					}
				}
				if (m_opr.top() == '#')//�������ջ��ֻʣ��#���������ϣ�ֱ��break
					break;
				calculator();//ִ��ջ������������������/���ȼ� <= �����ջ�������ȼ�����ջ�����������#����������������ǡ�������
			}
			if ((*it != '=')&&(*it != 'n') && (*it != 't') && (*it != 's')) {//���itָ����=����û���,�Ҳ���n,t,s��ǰ���Ѿ����ָ������ѹջ�����ﲻ��Ҫ��ѹջ��
				m_opr.push(*it);//���������ջ��������������ȼ� > �����ջ�������ȼ���
				if (*it == ')')//��ջ����')'����
					m_opr.pop();
			}
			++it;//������ɨ��
		}
	}
	return m_num.top();//���ؼ�������ע������ջ��ʱ�ǿ�
}