#ifndef DATABANK_H_
#define DATABANK_H_

//î•ñ•Û‘¶ƒNƒ‰ƒX
class DataBank
{
public:
	static DataBank* Instance();

protected:
	DataBank() {};
	~DataBank() {};

private:
	static DataBank* p_instance;
};

#endif // !DATABANK_H_
