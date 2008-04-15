# To change this template, choose Tools | Templates
# and open the template in the editor.

require 'loudmouth'
require 'glib2'

puts "Enter your JID: "
jid = gets.chomp

puts "Enter connect host: "
host = gets.chomp

puts "Enter your password: "
password = gets.chomp

if /(.+)@(.+)/ =~ jid
  login = $1
end

puts "Logging in as '#{login}' to '#{host}'"

main_loop = GLib::MainLoop.new

conn = LM::Connection.new(host)
conn.jid = jid
conn.ssl = LM::SSL.new
conn.ssl.use_starttls = true
conn.ssl.require_starttls = true

recipient = ""

conn.open do |result|
  puts "Connection open block"
  if result
    puts "Connection opened correctly"
    conn.authenticate(login, password, "Test") do |auth_result|
      unless auth_result
        puts "Failed to authenticate"
      end
      authenticated_cb(conn)
      main_loop.quit
    end
  else
    puts "Failed to connect"
    main_loop.quit
  end
end

def authenticated_cb(conn)
  puts "Authenticated!"
  puts "Who do you want to message: "
  recipient = gets.chomp
  
  puts "Enter message: "
  body = gets.chomp
  
  m = LM::Message.new(recipient, LM::MessageType::MESSAGE)
  m.node.add_child('body', body)
  
  conn.send(m)
  conn.close
  
  puts "Message sent to #{recipient}"
end

main_loop.run

puts "Quitting"
