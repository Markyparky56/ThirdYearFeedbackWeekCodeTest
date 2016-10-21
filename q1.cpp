int Foo(int x)
{
  int returnValue = 0;
  for(int i = 0; i < x; i++)
  {
    returnValue += i;
  }
  return returnValue;
}

int main()
{
  int num;
  num = Foo(10);
  return 0;
}
