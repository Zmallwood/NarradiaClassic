#!/usr/bin/perl

$running = "true";

while ($running eq "true") {
    print "Narradia Map Generator\n";
    print "======================\n";
    print "1. Generate new world map\n";
    print "2. Exit\n";
    $menu_select = <STDIN>;
    chomp $menu_select;

    if ($menu_select == "1") {
        print "Generating world map...\n";

        $world_width = 5;
        $world_height = 5;
        $world_area_width = 300;
        $world_area_height = 300;

        for ($wy = 0; $wy < $world_height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                for ($way = 0; $way < $world_area_height; $way = $way + 1) {
                    for ($wax = 0; $wax < $world_area_width; $wax = $wax + 1) {
                        print ">Generating tile at map ($wx, $wy) with coord $wax, $way\n";
                    }
                }
            }
        }

        $running = "false";
    }
    elsif ($menu_select == "2") {
        print "Exiting program.\n";
        $running = "false";
    }

}
