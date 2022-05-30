FROM python:3.9.5
RUN mkdir substringmatch
WORKDIR /substringmatch
COPY requirements.txt .
RUN apt-get update -y
RUN apt-get install build-essential -y
RUN pip install -r requirements.txt
ADD . /substringmatch
RUN c++ -O3 -Wall -shared -std=c++11 -fPIC $(python -m pybind11 --includes) substringmatch.cpp -o substringmatch$(python-config --extension-suffix)

EXPOSE 6688
CMD ["python", "main.py"]
