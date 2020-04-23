#!/usr/bin/env ruby

require "ckb"
require "json"


data_path = ARGV[0]
template_path = "debug-new.json"

data = File.read(data_path)
tx_template = File.read(template_path)

data_hash = CKB::Blake2b.hexdigest(data)
data_hex = CKB::Utils.bin_to_hex(data)


tx_template_json = JSON.parse(tx_template)

tx_template_json["mock_info"]["cell_deps"][0]["data"] = data_hex
tx_template_json["mock_info"]["inputs"][0]["output"]["lock"]["code_hash"] = data_hash

tx_template_json["tx"]["outputs"][0]["lock"]["code_hash"] =  data_hash
#tx_template_json["tx"]["outputs"][0]["type"]["code_hash"] =  data_hash

f = File.open("tx-mocked.json",mode="w")

tx_mocked = JSON.pretty_generate(tx_template_json)
f.write(tx_mocked)




