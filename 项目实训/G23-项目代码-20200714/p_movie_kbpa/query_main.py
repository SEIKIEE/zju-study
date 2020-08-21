#!/usr/bin/python
# encoding=utf-8

import sys
import jena_sparql_endpoint
import question2sparql

if __name__ == '__main__':
    fuseki = jena_sparql_endpoint.JenaFuseki()
    q2s = question2sparql.Question2Sparql(
        ['/root/KB_query/external_dict/movie_title.txt',
         '/root/KB_query/external_dict/person_name.txt'])

    question = sys.argv[1]
    my_query = q2s.get_sparql(question.decode('utf-8'))
    if my_query is not None:
        result = fuseki.get_sparql_result(my_query)
        value = fuseki.get_sparql_result_value(result)

        if isinstance(value, bool):
            if value is True:
                print 'Yes'
            else:
                print 'I don\'t know. :('
        else:
            if len(value) == 0:
                print '让我想想……'
            elif len(value) == 1:
                print value[0]
            else:
                output = ''
                for v in value:
                    output += v + u'、'
                print output[0:-1].encode(encoding="utf-8")

    else:
        print '换个问题问我吧 :）'
