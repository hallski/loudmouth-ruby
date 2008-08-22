require File.dirname(__FILE__) + '/spec_helper'
`cd #{File.dirname(__FILE__) + '/..'} && ruby extconf.rb configure && make clean && make`
require File.dirname(__FILE__) + '/../loudmouth.bundle'

describe "Basic LM::Message" do

  it 'should send an iq and receive a reply' do
    main_loop = GLib::MainLoop.new
    conn = LM::Connection.new
    conn.jid = 'vertebra-client@localhost'

    conn.set_disconnect_handler do |reason|
      puts "Disconnected"
      main_loop.quit
    end

    conn.open do |result|
      puts "Connection open block #{result.to_s}"
      if result
        puts "Connection opened correctly"
        conn.authenticate('vertebra-client', 'testing', "agent") do |auth_result|
          unless auth_result
            puts "Failed to authenticate"
          end
        end
        m = LM::Message.new('vertebra-client@localhost/agent', LM::MessageType::IQ)
        m.node.value = "<op></op>"
        conn.send(m) do |answer|
          puts "ANSWER #{answer.inspect}"
          @answer_from_block = answer
        end
        @answer_from_block.should_not be(nil)
        conn.close
      else
        puts "Failed to connect"
        main_loop.quit
      end
    end
    
    main_loop.run
    
  end

end