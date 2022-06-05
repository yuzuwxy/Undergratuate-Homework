library verilog;
use verilog.vl_types.all;
entity control is
    port(
        din             : in     vl_logic_vector(7 downto 0);
        clk             : in     vl_logic;
        rst             : in     vl_logic;
        z               : in     vl_logic;
        cpustate        : in     vl_logic_vector(1 downto 0);
        alus            : out    vl_logic_vector(3 downto 0);
        pcload          : out    vl_logic;
        drload          : out    vl_logic;
        pcbus           : out    vl_logic;
        pcinc           : out    vl_logic;
        drlbus          : out    vl_logic;
        drhbus          : out    vl_logic;
        irload          : out    vl_logic;
        membus          : out    vl_logic;
        busmem          : out    vl_logic;
        write           : out    vl_logic;
        read            : out    vl_logic;
        trload          : out    vl_logic;
        trbus           : out    vl_logic;
        arload          : out    vl_logic;
        rbus            : out    vl_logic;
        rload           : out    vl_logic;
        acload          : out    vl_logic;
        acbus           : out    vl_logic;
        zload           : out    vl_logic;
        zbus            : out    vl_logic;
        irbus           : out    vl_logic;
        clr             : out    vl_logic
    );
end control;
