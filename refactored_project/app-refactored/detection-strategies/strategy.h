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


class Strategy16X0Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy7X0Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy0X12Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy16X12Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy7X12Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy0X3Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy16X3Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}


class Strategy7X3Y : public Strategy 
{
public:
    void execute(Deplacement &deplacement) override;
}
