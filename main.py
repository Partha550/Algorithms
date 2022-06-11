from flask import Flask, request
from flask_restful import Api, Resource
from substringmatch import SubstringMatch
from subsequencematch import SubsequenceMatch
import json
import os

app = Flask(__name__)
api = Api(app)


class Substrings(Resource):
    def post(self):
        data = request.get_json()
        #  print(data)
        #  data = json.loads(data)
        X = data["X"]
        Y = data["Y"]
        match = SubstringMatch(X, Y)
        substrings = match.find_largest_substrings(wrt=X)
        response = json.dumps(substrings)
        return response

class Subsequence(Resource):
    def get(self):
        data = request.get_json()
        #  print(data)
        #  data = json.loads(data)
        X = data["X"]
        Y = data["Y"]
        match = SubsequenceMatch(X, Y)
        substrings = match.find_largest_subsequence()
        response = json.dumps(substrings)
        return response


api.add_resource(Substrings, "/")
api.add_resource(Subsequence, "/subsequencematch")
if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=6688)
