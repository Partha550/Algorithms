from flask import Flask, request
from flask_restful import Api, Resource
from substringmatch import SubstringMatch
import json
import os

app = Flask(__name__)
api = Api(app)


class Classify(Resource):
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


api.add_resource(Classify, "/")
if __name__ == "__main__":
    app.run(debug=True, host="0.0.0.0", port=6688)
