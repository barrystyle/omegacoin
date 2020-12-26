// Copyright (c) 2020 barrystyle
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <anonmsg.h>

#include <net_processing.h>
#include <net.h>
#include <rpc/client.h>
#include <rpc/server.h>
#include <rpc/protocol.h>
#include <utilstrencodings.h>
#include <boost/exception/to_string.hpp>

#include <univalue.h>

UniValue sendanonmsg(const UniValue& params, bool fHelp)
{
    UniValue result(UniValue::VARR);
    std::string strMsg = params[0].get_str();
    if (strMsg.empty()) {
        return result;
    }

    //! create and relay a message
    CAnonMsg testCase;
    testCase.setMessage(strMsg);

    //! relay message and store
    testCase.Relay();
    mapAnonMsgSeen.insert(std::make_pair(testCase.GetHash(),testCase));
    result.push_back("ok");

    return result;
}

UniValue listanonmsg(const UniValue& params, bool fHelp)
{
    UniValue ret(UniValue::VARR);
    for (auto t=mapAnonMsgSeen.begin(); t!=mapAnonMsgSeen.end(); ++t) {
        LogPrintf("test test  %s, %s\n", t->first.ToString(), t->second.getMessage());
    }




    for (auto message=mapAnonMsgSeen.begin(); message!=mapAnonMsgSeen.end(); ++message) {
        UniValue obj(UniValue::VOBJ);
        obj.push_back(Pair("timestamp", message->second.getTime()));
        obj.push_back(Pair("message", message->second.getMessage()));
        ret.push_back(obj);
    }

    return ret;
}