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

        open(DATA, ">World.conf") or die "Couldn't open file World.conf, $!";

        print DATA "Width=$world_width\n";
        print DATA "Height=$world_height\n";

        my $global_x;
        my $global_y;

        my @tiles;
        my @elevs;
        my @objects;
        my @reds;
        my @greens;
        my @blues;
        my @normalsx;
        my @normalsy;
        my @normalsz;

        for ($wy = 0; $wy < $world_height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                for ($way = 0; $way < $world_area_height; $way = $way + 1) {
                    for ($wax = 0; $wax < $world_area_width; $wax = $wax + 1) {
                        $global_x = $wx*$world_area_width + $wax;
                        $global_y = $wy*$world_area_height+ $way;

                        $tiles[$global_x][$global_y] = "GroundWater";
                        $elevs[$global_x][$global_y] = 0.0;
                        $reds[$global_x][$global_y] = 1.0;
                        $greens[$global_x][$global_y] = 1.0;
                        $blues[$global_x][$global_y] = 1.0;
                        $normalsx[$global_x][$global_y] = 0.0;
                        $normalsy[$global_x][$global_y] = 1.0;
                        $normalsz[$global_x][$global_y] = 0.0;
                        $objects[$global_x][$global_y] = "";
                    }
                }
            }
        }
        $num_tiles_x = $world_width*$world_area_width;
        $num_tiles_y = $world_height*$world_area_height;
        $max_side = $num_tiles_x > $num_tiles_y ? $num_tiles_x : $num_tiles_y;
        print "Max side: $max_side\n";
        $r = $max_side/2*90/100;
        $center_x = $num_tiles_x/2;
        $center_y = $num_tiles_y/2;

        print "Continent radius: $r\n";

        for ($y = $center_y - $r; $y <= $center_y + $r; $y = $y + 1) {
            for ($x = $center_x - $r; $x <= $center_x + $r; $x = $x + 1) {
                $dx = $x - $center_x;
                $dy = $y - $center_y;

                if ($dx*$dx + $dy*$dy < $r*$r) {
                    $tiles[$x][$y] = "Ground";
                }
            }
        }

        for ($wy = 0; $wy < $world_height; $wy = $wy + 1) {
            for ($wx = 0; $wx < $world_width; $wx = $wx + 1) {
                print ">Generating tile at map ($wx, $wy)\n";

                print DATA "$wx,$wy=Map$wx\_$wy.map\n";

                open(DATA_AREA, ">Map$wx\_$wy.map") or die "Couldn't open file Map$wx\_$wy.map, $!";
                print DATA_AREA "<width>$world_area_width</width>\n";
                print DATA_AREA "<height>$world_area_height</height>\n";

                for ($way = 0; $way < $world_area_height; $way = $way + 1) {
                    for ($wax = 0; $wax < $world_area_width; $wax = $wax + 1) {
                        $global_x = $wx*$world_area_width + $wax;
                        $global_y = $wy*$world_area_height+ $way;

                        print DATA_AREA "<tile>\n";

                        print DATA_AREA "  <ground>$tiles[$global_x][$global_y]</ground>\n";

                        print DATA_AREA "  <elevation>";
                        printf DATA_AREA '%.3f', $elevs[$global_x][$global_y];
                        print DATA_AREA "f</elevation>\n";

                        print DATA_AREA "  <red>";
                        printf DATA_AREA '%.3f', $reds[$global_x][$global_y];
                        print DATA_AREA "f</red>\n";

                        print DATA_AREA "  <green>";
                        printf DATA_AREA '%.3f', $greens[$global_x][$global_y];
                        print DATA_AREA "f</green>\n";

                        print DATA_AREA "  <blue>";
                        printf DATA_AREA '%.3f', $blues[$global_x][$global_y];
                        print DATA_AREA "f</blue>\n";

                        print DATA_AREA "  <objects>\n";

                        if ($objects[$global_x][$global_y] ne "") {
                            print DATA_AREA "    <object>\n";
                            print DATA_AREA "      <type>$objects[$global_x][$global_y]</type>\n";
                            print DATA_AREA "      <quantity>1</quantity>\n";
                            print DATA_AREA "    </object>\n";
                        }

                        print DATA_AREA "  </objects>\n";

                        print DATA_AREA "  <normal>\n";

                        print DATA_AREA "    <x>";
                        printf DATA_AREA '%.3f', $normalsx[$global_x][$global_y];
                        print DATA_AREA "f</x>\n";

                        print DATA_AREA "    <y>";
                        printf DATA_AREA '%.3f', $normalsy[$global_x][$global_y];
                        print DATA_AREA "f</y>\n";

                        print DATA_AREA "    <z>";
                        printf DATA_AREA '%.3f', $normalsz[$global_x][$global_y];
                        print DATA_AREA "f</z>\n";

                        print DATA_AREA "  </normal>\n";

                        print DATA_AREA "</tile>\n";
                    }
                }

                close(DATA_AREA) || die "Couldn't close file properly";
            }
        }

        close(DATA) || die "Couldn't close file properly";

        $running = "false";
    }
    elsif ($menu_select == "2") {
        print "Exiting program.\n";
        $running = "false";
    }

}
