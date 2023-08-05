class Strategy 
{
public:
    virtual ~Strategy() {}
    virtual void execute(Deplacement &deplacement) = 0;
};

class Strategy0X0YUp : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class Strategy0X0YRight : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS16X0Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS7X0Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS0X12Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS16X12Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS7X12Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS0X3Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS16X3Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}

class POS7X3YHAUT : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}
