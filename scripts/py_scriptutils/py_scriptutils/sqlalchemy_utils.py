from sqlalchemy import Column, Integer, String, ForeignKey, DateTime

def IdColumn():
    return Column(Integer, primary_key=True, autoincrement=True)


def ForeignId(name: str, nullable: bool = False):
    return Column(Integer, ForeignKey(name), nullable=nullable)


def IntColumn(nullable: bool = False):
    return Column(Integer, nullable=nullable)


def StrColumn(nullable: bool = False):
    return Column(String, nullable=nullable)

def DateTimeColumn(**kwargs):
    return Column(DateTime, **kwargs)